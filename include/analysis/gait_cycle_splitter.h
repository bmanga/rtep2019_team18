#ifndef RTEP_TEAM18_GAIT_CYCLE_SPLITTER_H
#define RTEP_TEAM18_GAIT_CYCLE_SPLITTER_H

#include <array>
#include <atomic>
#include <boost/circular_buffer.hpp>
#include <cassert>
#include <chrono>
#include <iostream>
#include <kfr/base.hpp>
#include <kfr/dft.hpp>
#include <kfr/dsp.hpp>
#include <kfr/io.hpp>
#include <mutex>
#include <numeric>
#include <thread>

#include <DspFilters/Dsp.h>
#include <DspFilters/Filter.h>

#include "peak_analysis.h"

using packaged_data = std::array<float, 20>;

template <class T>
class mutexed_data {
 public:
  void set(const T &data)
  {
    std::unique_lock<std::mutex> l(m_data_mut);
    m_data = data;
  }

  T get()
  {
    std::unique_lock<std::mutex> l(m_data_mut);
    T data = m_data;
    return data;
  }

 private:
  std::mutex m_data_mut;
  T m_data;
};

class gait_cycle_splitter {
 public:
  float getDominantFrequency(
      double sampling_freq,
      kfr::univector<kfr::complex<kfr::fbase>> datapoints)
  {
    datapoints = datapoints - kfr::mean(datapoints);

    auto size = datapoints.size();

    const kfr::dft_plan<kfr::fbase> dft(size);

    kfr::univector<kfr::complex<kfr::fbase>> out =
        {};  // kfr::scalar(kfr::qnan);

    out.resize(size);

    // allocate work buffer for fft (if needed)
    kfr::univector<kfr::u8> temp(dft.temp_size);

    // perform forward fft
    dft.execute(out, datapoints, temp);

    out /= size;

    kfr::univector<kfr::fbase> abs_out = kfr::real(kfr::cabs(out));

    auto max_it = std::max_element(abs_out.begin(), abs_out.begin() + size / 2);
    size_t max_idx = std::distance(abs_out.begin(), max_it);

    kfr::univector<kfr::fbase> freq;
    freq.resize(size);
    std::iota(freq.begin(), freq.end(), 0);

    auto T = (double)size / sampling_freq;

    freq /= T;

    std::cout << "max freq: " << freq[max_idx] << "\n";

    return freq[max_idx];
  }

  kfr::univector<kfr::fbase> getFilteredData(double sampling_freq,
                                             double dominant_freq,
                                             kfr::univector<double> datapoints)
  {
    Dsp::SimpleFilter<Dsp::Butterworth::BandPass<10>, 1> f;
    f.setup(5,              // order
            sampling_freq,  // sample rate
            dominant_freq,  // center frequency
            0.2             // band width
    );

    double *datap = datapoints.data();

    f.process(datapoints.size(), &datap);
    std::reverse(datapoints.begin(), datapoints.end());
    f.process(datapoints.size(), &datap);

    return datapoints;
  }

  void update_cycle_freq()
  {
    kfr::univector<double> fsr_points;
    while (m_run_freq_updater) {
      std::this_thread::sleep_for(std::chrono::seconds(5));
      m_cycle_freq_mut.lock();
      m_cur_sampling_freq = 1 / (m_timepoints[1] - m_timepoints[0]);
      double *data = m_fsr_points.linearize();
      fsr_points.assign(data, data + m_fsr_points.size());
      m_cycle_freq_mut.unlock();

      m_cur_cycle_freq = getDominantFrequency(m_cur_sampling_freq, fsr_points);
    }
  }

  gait_cycle_splitter()
      : m_timepoints(256),
        m_fsr_points(256),
        m_data_points(256),
        m_run_freq_updater{true},
        m_freq_thread(&gait_cycle_splitter::update_cycle_freq, this)
  {
  }

  ~gait_cycle_splitter()
  {
    m_run_freq_updater = false;
    m_freq_thread.join();
  }

  void add_cycle_points(double tp, double dp, packaged_data pd)
  {
    std::unique_lock<std::mutex> l(m_cycle_freq_mut);
    m_timepoints.push_back(tp);
    m_fsr_points.push_back(dp);
    m_data_points.push_back(pd);
  }

  std::pair<double, double> latest_gait_cycle()
  {
    kfr::univector<double> filtered;
    kfr::univector<double> timepoints;
    kfr::univector<packaged_data> data;
    m_cycle_freq_mut.lock();

    double *filtered_data = m_fsr_points.linearize();
    double *timepoints_data = m_timepoints.linearize();
    packaged_data *series_data = m_data_points.linearize();

    filtered.assign(filtered_data, filtered_data + m_fsr_points.size());
    timepoints.assign(timepoints_data, timepoints_data + m_fsr_points.size());
    data.assign(series_data, series_data + m_data_points.size());

    m_cycle_freq_mut.unlock();

    filtered = getFilteredData(m_cur_sampling_freq.load(),
                               m_cur_cycle_freq.load(), filtered);

    std::vector<int> peaks;
    findPeaks(filtered, peaks);

    if (peaks.size() < 3)
      return {0, 0};

    std::array<kfr::univector<float>, 20> linearized_dataseries;

    for (int j = peaks[peaks.size() - 3]; j < peaks[peaks.size() - 2]; ++j) {
      for (int k = 0; k < 20; ++k) {
        linearized_dataseries[k].push_back(series_data[j][k]);
      }
    }

    m_latest_gait_data.set(linearized_dataseries);

    return {timepoints[peaks[peaks.size() - 3]],
            timepoints[peaks[peaks.size() - 2]]};
  }

  std::array<kfr::univector<float>, 20> get_latest_cycle_data()
  {
    return m_latest_gait_data.get();
  }

 private:
  std::mutex m_cycle_freq_mut;

  mutexed_data<std::array<kfr::univector<float>, 20>> m_latest_gait_data;

  boost::circular_buffer<double> m_timepoints;
  boost::circular_buffer<double> m_fsr_points;

  boost::circular_buffer<packaged_data> m_data_points;

  std::atomic<double> m_cur_cycle_freq;
  std::atomic<double> m_cur_sampling_freq;
  std::atomic_bool m_run_freq_updater;

  std::thread m_freq_thread;
};

#endif  // RTEP_TEAM18_GAIT_CYCLE_SPLITTER_H
