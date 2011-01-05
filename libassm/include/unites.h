#if !defined(UNITES_H_3SQ9F9YZ)
#define UNITES_H_3SQ9F9YZ

static const double amplitude_reference = 0.000001; // 10^-6

double to_volume_from_amplitude(double amplitude);
double to_amplitude_from_volume(double volume);
double to_bark_from_frequence(double frequence);
double to_frequence_from_bark(double bark);

#endif /* end of include guard: UNITES_H_3SQ9F9YZ */
