#include <cstdlib>
#include <cmath>
#include <glog/logging.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  double xi, yi, x[10], y[10];

  for (int i = 0; i < 10; i++)
    {
      x[i] = i + 0.5 * sin (i);
      y[i] = i + cos (i * i);
      printf ("%g %g\n", x[i], y[i]);
    }
  printf("\n");

  gsl_interp_accel *acc
    = gsl_interp_accel_alloc ();

  gsl_spline *spline
    = gsl_spline_alloc (gsl_interp_cspline, 10);
  gsl_spline_init (spline, x, y, 10);

  for (xi = x[0]; xi < x[9]; xi += 0.01)
    {
      yi = gsl_spline_eval (spline, (double)xi, acc);
      printf ("%g %g\n", xi, yi);
    }
  gsl_spline_free (spline);
    gsl_interp_accel_free (acc);
  LOG(INFO) << "test_gsl ends";
  return EXIT_SUCCESS;
}
