#ifndef RTEP_TEAM18_PEAK_ANALYSIS_H
#define RTEP_TEAM18_PEAK_ANALYSIS_H

#include <kfr/base.hpp>
#include <vector>

#define EPS 2.2204e-16

void diff(kfr::univector<double> in, kfr::univector<double> &out)
{
  out = kfr::univector<double>(in.size() - 1);

  for (int i = 1; i < in.size(); ++i)
    out[i - 1] = in[i] - in[i - 1];
}

void vectorProduct(kfr::univector<double> a,
                   kfr::univector<double> b,
                   kfr::univector<double> &out)
{
  out = kfr::univector<double>(a.size());

  for (int i = 0; i < a.size(); ++i)
    out[i] = a[i] * b[i];
}

void findIndicesLessThan(kfr::univector<double> in,
                         float threshold,
                         std::vector<int> &indices)
{
  for (int i = 0; i < in.size(); ++i)
    if (in[i] < threshold)
      indices.push_back(i + 1);
}

void selectElements(kfr::univector<double> in,
                    std::vector<int> indices,
                    kfr::univector<double> &out)
{
  for (int i = 0; i < indices.size(); ++i)
    out.push_back(in[indices[i]]);
}

void selectElements(std::vector<int> in,
                    std::vector<int> indices,
                    std::vector<int> &out)
{
  for (int i = 0; i < indices.size(); ++i)
    out.push_back(in[indices[i]]);
}

void signVector(kfr::univector<double> in, std::vector<int> &out)
{
  out = std::vector<int>(in.size());

  for (int i = 0; i < in.size(); ++i) {
    if (in[i] > 0)
      out[i] = 1;
    else if (in[i] < 0)
      out[i] = -1;
    else
      out[i] = 0;
  }
}

void findPeaks(kfr::univector<double> x0, std::vector<int> &peakInds)
{
  int minIdx = distance(x0.begin(), min_element(x0.begin(), x0.end()));
  int maxIdx = distance(x0.begin(), max_element(x0.begin(), x0.end()));

  float sel = (x0[maxIdx] - x0[minIdx]) / 4.0;

  int len0 = x0.size();

  kfr::univector<double> dx;
  diff(x0, dx);
  replace(dx.begin(), dx.end(), 0.0, -EPS);
  kfr::univector<double> dx0(dx.begin(), dx.end() - 1);
  kfr::univector<double> dx1(dx.begin() + 1, dx.end());
  kfr::univector<double> dx2;

  vectorProduct(dx0, dx1, dx2);

  std::vector<int> ind;
  findIndicesLessThan(dx2, 0, ind);  // Find where the derivative changes sign

  kfr::univector<double> x;

  std::vector<int> indAux(ind.begin(), ind.end());
  selectElements(x0, indAux, x);
  x.insert(x.begin(), x0[0]);
  x.insert(x.end(), x0[x0.size() - 1]);
  ;

  ind.insert(ind.begin(), 0);
  ind.insert(ind.end(), len0);

  int minMagIdx = distance(x.begin(), min_element(x.begin(), x.end()));
  float minMag = x[minMagIdx];
  float leftMin = minMag;
  int len = x.size();

  if (len > 2) {
    float tempMag = minMag;
    bool foundPeak = false;
    int ii;

    // Deal with first point a little differently since tacked it on
    // Calculate the sign of the derivative since we tacked the first
    //  point on it does not neccessarily alternate like the rest.
    kfr::univector<double> xSub0(x.begin(),
                                 x.begin() + 3);  // tener cuidado subvector
    kfr::univector<double> xDiff;                 // tener cuidado subvector
    diff(xSub0, xDiff);

    std::vector<int> signDx;
    signVector(xDiff, signDx);

    if (signDx[0] <= 0)  // The first point is larger or equal to the second
    {
      if (signDx[0] == signDx[1])  // Want alternating signs
      {
        x.erase(x.begin() + 1);
        ind.erase(ind.begin() + 1);
        len = len - 1;
      }
    }
    else  // First point is smaller than the second
    {
      if (signDx[0] == signDx[1])  // Want alternating signs
      {
        x.erase(x.begin());
        ind.erase(ind.begin());
        len = len - 1;
      }
    }

    if (x[0] >= x[1])
      ii = 0;
    else
      ii = 1;

    float maxPeaks = ceil((float)len / 2.0);
    std::vector<int> peakLoc(maxPeaks, 0);
    kfr::univector<double> peakMag(maxPeaks, 0.0);
    int cInd = 1;
    int tempLoc;

    while (ii < len) {
      ii = ii + 1;  // This is a peak
      // Reset peak finding if we had a peak and the next peak is bigger
      // than the last or the left min was small enough to reset.
      if (foundPeak) {
        tempMag = minMag;
        foundPeak = false;
      }

      // Found new peak that was lager than temp mag and selectivity larger
      // than the minimum to its left.

      if (x[ii - 1] > tempMag && x[ii - 1] > leftMin + sel) {
        tempLoc = ii - 1;
        tempMag = x[ii - 1];
      }

      // Make sure we don't iterate past the length of our vector
      if (ii == len)
        break;  // We assign the last point differently out of the loop

      ii = ii + 1;  // Move onto the valley

      // Come down at least sel from peak
      if (!foundPeak && tempMag > sel + x[ii - 1]) {
        foundPeak = true;  // We have found a peak
        leftMin = x[ii - 1];
        peakLoc[cInd - 1] = tempLoc;  // Add peak to index
        peakMag[cInd - 1] = tempMag;
        cInd = cInd + 1;
      }
      else if (x[ii - 1] < leftMin)  // New left minima
        leftMin = x[ii - 1];
    }

    // Check end point
    if (x[x.size() - 1] > tempMag && x[x.size() - 1] > leftMin + sel) {
      peakLoc[cInd - 1] = len - 1;
      peakMag[cInd - 1] = x[x.size() - 1];
      cInd = cInd + 1;
    }
    else if (!foundPeak &&
             tempMag > minMag)  // Check if we still need to add the last point
    {
      peakLoc[cInd - 1] = tempLoc;
      peakMag[cInd - 1] = tempMag;
      cInd = cInd + 1;
    }

    // Create output
    if (cInd > 0) {
      std::vector<int> peakLocTmp(peakLoc.begin(), peakLoc.begin() + cInd - 1);
      selectElements(ind, peakLocTmp, peakInds);
      // peakMags = kfr::univector<double>(peakLoc.begin(),
      // peakLoc.begin()+cInd-1);
    }
  }
}

#endif  // RTEP_TEAM18_PEAK_ANALYSIS_H
