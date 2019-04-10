import matplotlib.pyplot as plt
import numpy as np
import json
from scipy import signal
import csv


def loadJsonData(filename):
    with open(filename, "r") as file:
        data = json.load(file)
        print(data)
        timepoints = list()
        datapoints = list()
        for timepoint in data.keys():
            timepoints.append(float(timepoint))
            datapoints.append(data[timepoint])# + data[timepoint]["FSR_R"][2])
        return timepoints, datapoints
    return None


def butter_lowpass(cutoff, fs, order=5):
    nyq = 0.5 * fs
    normal_cutoff = cutoff / nyq
    print(normal_cutoff)
    b, a = signal.butter(order, normal_cutoff, btype='low', analog=False)
    return b, a

def butter_lowpass_filter(data, cutoff, fs, order=5):
    b, a = butter_lowpass(cutoff, fs, order=order)
    y = signal.filtfilt(b, a, data)
    return y

def butter_bandpass(cutoff, fs, order=5):
    nyq = 0.5 * fs
    normal_cutoff = np.array(cutoff) / nyq
    print(normal_cutoff)
    b, a = signal.butter(order, normal_cutoff, btype='band', analog=False)
    return b, a

def butter_bandpass_filter(data, cutoff, fs, order=5):
    b, a = butter_bandpass(cutoff, fs, order=order)
    y = signal.filtfilt(b, a, data)
    return y


def plotFFT(tp, dp):
    n = len(dp)
    k = np.arange(n)
    T = n / ( 1 / (tp[1] - tp[0]))
    freq = k / T
    freq = freq[range(int(n/2))]
    dpfilt = dp - np.mean(dp)
    Y = np.fft.fft(dpfilt) / n
    Y = Y[range(int(n/2))]

    fig, ax = plt.subplots(2, 1)
    ax[0].set_xticks(np.arange(tp[0], tp[-1], 1))
    ax[0].set_yticks(np.arange(-2, 2, 0.5))
    ax[0].set_xlabel('Time')
    ax[0].set_ylabel('Amplitude')
    ax[0].grid(True)
    ax[0].plot(tp, dpfilt)
    ax[1].set_xlim(0, 8)
    ax[1].set_ylim(0, 0.4)
    ax[1].plot(freq, abs(Y), 'r')  # plotting the spectrum
    ax[1].set_xlabel('Freq (Hz)')
    ax[1].set_ylabel('|Y(freq)|')
    ax[1].set_xticks(np.arange(0, 8, 0.5))
    ax[1].grid(True)

    plt.show()
    return freq[np.argmax(abs(Y))]

def peakAnalysis(tp, dp):
    peaks, _ = signal.find_peaks(dp)

    ax1 = plt.figure()
    #ax2.set_xlim(ax1.get_xlim())
    plt.xticks(list(map(lambda x : tp[x], peaks)))
    plt.plot(tp, dp)
    for p in peaks:
        plt.axvline(x=tp[p])
    plt.show()
    return peaks


def generateDataset(data, times, peaks, label, filename):
    series = data[0].keys()

    with open(filename, mode='w') as employee_file:
        featurev_writer = csv.writer(employee_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

        for j in range(1, len(peaks)):
            feature_vector = []
            for s in series:
                rb = 0
                if s == "FSR_R" or s == "FSR_L":
                    rb = 2

                for k in range(rb, 3):
                    d = [x[s][k] for x in data[peaks[j - 1]:peaks[j]]]
                    t = times[peaks[j - 1]:peaks[j]]
                    # Resample
                    d, t = signal.resample(d, 20, t)
                    feature_vector += list(d)

            feature_vector.append(label)
            featurev_writer.writerow(feature_vector)


def plotAndGenerateDS(tp, dp, label, filename):
    fsr_l = [x["FSR_L"][2] for x in dp]

    freq = plotFFT(tp, fsr_l)
    filtered = butter_bandpass_filter(fsr_l, [freq - 0.1, freq + 0.1], 1 / (tp[1] - tp[0]))
    peaks = peakAnalysis(tp, filtered)
    generateDataset(dp, tp, peaks=peaks, label=label, filename=filename)


tpg, datag = loadJsonData("savedata/luca-good-9.04.json")
tpb, datab = loadJsonData("savedata/luca-bad-9.04.json")
tpb2, datab2 = loadJsonData("savedata/luca-bad-footdrop-9.04.json")

start = 0
end = -1
tpg = tpg[start:end]
tpb = tpb[start:end]

datag = datag[start:end]
datab = datab[start:end]

plotAndGenerateDS(tpg, datag, label="good", filename="processeddata/luca_good.csv")
plotAndGenerateDS(tpb, datab, label="hemiplegic", filename="processeddata/luca_hemiplegic.csv")
plotAndGenerateDS(tpb2, datab2, label="dragging", filename="processeddata/luca_dragging.csv")

