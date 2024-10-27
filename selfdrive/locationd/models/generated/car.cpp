#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4523861128599971785) {
   out_4523861128599971785[0] = delta_x[0] + nom_x[0];
   out_4523861128599971785[1] = delta_x[1] + nom_x[1];
   out_4523861128599971785[2] = delta_x[2] + nom_x[2];
   out_4523861128599971785[3] = delta_x[3] + nom_x[3];
   out_4523861128599971785[4] = delta_x[4] + nom_x[4];
   out_4523861128599971785[5] = delta_x[5] + nom_x[5];
   out_4523861128599971785[6] = delta_x[6] + nom_x[6];
   out_4523861128599971785[7] = delta_x[7] + nom_x[7];
   out_4523861128599971785[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3940455236356545429) {
   out_3940455236356545429[0] = -nom_x[0] + true_x[0];
   out_3940455236356545429[1] = -nom_x[1] + true_x[1];
   out_3940455236356545429[2] = -nom_x[2] + true_x[2];
   out_3940455236356545429[3] = -nom_x[3] + true_x[3];
   out_3940455236356545429[4] = -nom_x[4] + true_x[4];
   out_3940455236356545429[5] = -nom_x[5] + true_x[5];
   out_3940455236356545429[6] = -nom_x[6] + true_x[6];
   out_3940455236356545429[7] = -nom_x[7] + true_x[7];
   out_3940455236356545429[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1374868943770561080) {
   out_1374868943770561080[0] = 1.0;
   out_1374868943770561080[1] = 0;
   out_1374868943770561080[2] = 0;
   out_1374868943770561080[3] = 0;
   out_1374868943770561080[4] = 0;
   out_1374868943770561080[5] = 0;
   out_1374868943770561080[6] = 0;
   out_1374868943770561080[7] = 0;
   out_1374868943770561080[8] = 0;
   out_1374868943770561080[9] = 0;
   out_1374868943770561080[10] = 1.0;
   out_1374868943770561080[11] = 0;
   out_1374868943770561080[12] = 0;
   out_1374868943770561080[13] = 0;
   out_1374868943770561080[14] = 0;
   out_1374868943770561080[15] = 0;
   out_1374868943770561080[16] = 0;
   out_1374868943770561080[17] = 0;
   out_1374868943770561080[18] = 0;
   out_1374868943770561080[19] = 0;
   out_1374868943770561080[20] = 1.0;
   out_1374868943770561080[21] = 0;
   out_1374868943770561080[22] = 0;
   out_1374868943770561080[23] = 0;
   out_1374868943770561080[24] = 0;
   out_1374868943770561080[25] = 0;
   out_1374868943770561080[26] = 0;
   out_1374868943770561080[27] = 0;
   out_1374868943770561080[28] = 0;
   out_1374868943770561080[29] = 0;
   out_1374868943770561080[30] = 1.0;
   out_1374868943770561080[31] = 0;
   out_1374868943770561080[32] = 0;
   out_1374868943770561080[33] = 0;
   out_1374868943770561080[34] = 0;
   out_1374868943770561080[35] = 0;
   out_1374868943770561080[36] = 0;
   out_1374868943770561080[37] = 0;
   out_1374868943770561080[38] = 0;
   out_1374868943770561080[39] = 0;
   out_1374868943770561080[40] = 1.0;
   out_1374868943770561080[41] = 0;
   out_1374868943770561080[42] = 0;
   out_1374868943770561080[43] = 0;
   out_1374868943770561080[44] = 0;
   out_1374868943770561080[45] = 0;
   out_1374868943770561080[46] = 0;
   out_1374868943770561080[47] = 0;
   out_1374868943770561080[48] = 0;
   out_1374868943770561080[49] = 0;
   out_1374868943770561080[50] = 1.0;
   out_1374868943770561080[51] = 0;
   out_1374868943770561080[52] = 0;
   out_1374868943770561080[53] = 0;
   out_1374868943770561080[54] = 0;
   out_1374868943770561080[55] = 0;
   out_1374868943770561080[56] = 0;
   out_1374868943770561080[57] = 0;
   out_1374868943770561080[58] = 0;
   out_1374868943770561080[59] = 0;
   out_1374868943770561080[60] = 1.0;
   out_1374868943770561080[61] = 0;
   out_1374868943770561080[62] = 0;
   out_1374868943770561080[63] = 0;
   out_1374868943770561080[64] = 0;
   out_1374868943770561080[65] = 0;
   out_1374868943770561080[66] = 0;
   out_1374868943770561080[67] = 0;
   out_1374868943770561080[68] = 0;
   out_1374868943770561080[69] = 0;
   out_1374868943770561080[70] = 1.0;
   out_1374868943770561080[71] = 0;
   out_1374868943770561080[72] = 0;
   out_1374868943770561080[73] = 0;
   out_1374868943770561080[74] = 0;
   out_1374868943770561080[75] = 0;
   out_1374868943770561080[76] = 0;
   out_1374868943770561080[77] = 0;
   out_1374868943770561080[78] = 0;
   out_1374868943770561080[79] = 0;
   out_1374868943770561080[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1405568563655631313) {
   out_1405568563655631313[0] = state[0];
   out_1405568563655631313[1] = state[1];
   out_1405568563655631313[2] = state[2];
   out_1405568563655631313[3] = state[3];
   out_1405568563655631313[4] = state[4];
   out_1405568563655631313[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1405568563655631313[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1405568563655631313[7] = state[7];
   out_1405568563655631313[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2452143806039032916) {
   out_2452143806039032916[0] = 1;
   out_2452143806039032916[1] = 0;
   out_2452143806039032916[2] = 0;
   out_2452143806039032916[3] = 0;
   out_2452143806039032916[4] = 0;
   out_2452143806039032916[5] = 0;
   out_2452143806039032916[6] = 0;
   out_2452143806039032916[7] = 0;
   out_2452143806039032916[8] = 0;
   out_2452143806039032916[9] = 0;
   out_2452143806039032916[10] = 1;
   out_2452143806039032916[11] = 0;
   out_2452143806039032916[12] = 0;
   out_2452143806039032916[13] = 0;
   out_2452143806039032916[14] = 0;
   out_2452143806039032916[15] = 0;
   out_2452143806039032916[16] = 0;
   out_2452143806039032916[17] = 0;
   out_2452143806039032916[18] = 0;
   out_2452143806039032916[19] = 0;
   out_2452143806039032916[20] = 1;
   out_2452143806039032916[21] = 0;
   out_2452143806039032916[22] = 0;
   out_2452143806039032916[23] = 0;
   out_2452143806039032916[24] = 0;
   out_2452143806039032916[25] = 0;
   out_2452143806039032916[26] = 0;
   out_2452143806039032916[27] = 0;
   out_2452143806039032916[28] = 0;
   out_2452143806039032916[29] = 0;
   out_2452143806039032916[30] = 1;
   out_2452143806039032916[31] = 0;
   out_2452143806039032916[32] = 0;
   out_2452143806039032916[33] = 0;
   out_2452143806039032916[34] = 0;
   out_2452143806039032916[35] = 0;
   out_2452143806039032916[36] = 0;
   out_2452143806039032916[37] = 0;
   out_2452143806039032916[38] = 0;
   out_2452143806039032916[39] = 0;
   out_2452143806039032916[40] = 1;
   out_2452143806039032916[41] = 0;
   out_2452143806039032916[42] = 0;
   out_2452143806039032916[43] = 0;
   out_2452143806039032916[44] = 0;
   out_2452143806039032916[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2452143806039032916[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2452143806039032916[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2452143806039032916[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2452143806039032916[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2452143806039032916[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2452143806039032916[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2452143806039032916[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2452143806039032916[53] = -9.8000000000000007*dt;
   out_2452143806039032916[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2452143806039032916[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2452143806039032916[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2452143806039032916[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2452143806039032916[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2452143806039032916[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2452143806039032916[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2452143806039032916[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2452143806039032916[62] = 0;
   out_2452143806039032916[63] = 0;
   out_2452143806039032916[64] = 0;
   out_2452143806039032916[65] = 0;
   out_2452143806039032916[66] = 0;
   out_2452143806039032916[67] = 0;
   out_2452143806039032916[68] = 0;
   out_2452143806039032916[69] = 0;
   out_2452143806039032916[70] = 1;
   out_2452143806039032916[71] = 0;
   out_2452143806039032916[72] = 0;
   out_2452143806039032916[73] = 0;
   out_2452143806039032916[74] = 0;
   out_2452143806039032916[75] = 0;
   out_2452143806039032916[76] = 0;
   out_2452143806039032916[77] = 0;
   out_2452143806039032916[78] = 0;
   out_2452143806039032916[79] = 0;
   out_2452143806039032916[80] = 1;
}
void h_25(double *state, double *unused, double *out_1023489145526815441) {
   out_1023489145526815441[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3807818720460521655) {
   out_3807818720460521655[0] = 0;
   out_3807818720460521655[1] = 0;
   out_3807818720460521655[2] = 0;
   out_3807818720460521655[3] = 0;
   out_3807818720460521655[4] = 0;
   out_3807818720460521655[5] = 0;
   out_3807818720460521655[6] = 1;
   out_3807818720460521655[7] = 0;
   out_3807818720460521655[8] = 0;
}
void h_24(double *state, double *unused, double *out_5500848379716595858) {
   out_5500848379716595858[0] = state[4];
   out_5500848379716595858[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4967073687351649239) {
   out_4967073687351649239[0] = 0;
   out_4967073687351649239[1] = 0;
   out_4967073687351649239[2] = 0;
   out_4967073687351649239[3] = 0;
   out_4967073687351649239[4] = 1;
   out_4967073687351649239[5] = 0;
   out_4967073687351649239[6] = 0;
   out_4967073687351649239[7] = 0;
   out_4967073687351649239[8] = 0;
   out_4967073687351649239[9] = 0;
   out_4967073687351649239[10] = 0;
   out_4967073687351649239[11] = 0;
   out_4967073687351649239[12] = 0;
   out_4967073687351649239[13] = 0;
   out_4967073687351649239[14] = 1;
   out_4967073687351649239[15] = 0;
   out_4967073687351649239[16] = 0;
   out_4967073687351649239[17] = 0;
}
void h_30(double *state, double *unused, double *out_6431998359533457045) {
   out_6431998359533457045[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7722235011757413206) {
   out_7722235011757413206[0] = 0;
   out_7722235011757413206[1] = 0;
   out_7722235011757413206[2] = 0;
   out_7722235011757413206[3] = 0;
   out_7722235011757413206[4] = 1;
   out_7722235011757413206[5] = 0;
   out_7722235011757413206[6] = 0;
   out_7722235011757413206[7] = 0;
   out_7722235011757413206[8] = 0;
}
void h_26(double *state, double *unused, double *out_516367605799594709) {
   out_516367605799594709[0] = state[7];
}
void H_26(double *state, double *unused, double *out_66315401586465431) {
   out_66315401586465431[0] = 0;
   out_66315401586465431[1] = 0;
   out_66315401586465431[2] = 0;
   out_66315401586465431[3] = 0;
   out_66315401586465431[4] = 0;
   out_66315401586465431[5] = 0;
   out_66315401586465431[6] = 0;
   out_66315401586465431[7] = 1;
   out_66315401586465431[8] = 0;
}
void h_27(double *state, double *unused, double *out_6411654288901885372) {
   out_6411654288901885372[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8549745750151713499) {
   out_8549745750151713499[0] = 0;
   out_8549745750151713499[1] = 0;
   out_8549745750151713499[2] = 0;
   out_8549745750151713499[3] = 1;
   out_8549745750151713499[4] = 0;
   out_8549745750151713499[5] = 0;
   out_8549745750151713499[6] = 0;
   out_8549745750151713499[7] = 0;
   out_8549745750151713499[8] = 0;
}
void h_29(double *state, double *unused, double *out_6136460226617379483) {
   out_6136460226617379483[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7212003667443021022) {
   out_7212003667443021022[0] = 0;
   out_7212003667443021022[1] = 1;
   out_7212003667443021022[2] = 0;
   out_7212003667443021022[3] = 0;
   out_7212003667443021022[4] = 0;
   out_7212003667443021022[5] = 0;
   out_7212003667443021022[6] = 0;
   out_7212003667443021022[7] = 0;
   out_7212003667443021022[8] = 0;
}
void h_28(double *state, double *unused, double *out_8791825661536103721) {
   out_8791825661536103721[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1753984006212631892) {
   out_1753984006212631892[0] = 1;
   out_1753984006212631892[1] = 0;
   out_1753984006212631892[2] = 0;
   out_1753984006212631892[3] = 0;
   out_1753984006212631892[4] = 0;
   out_1753984006212631892[5] = 0;
   out_1753984006212631892[6] = 0;
   out_1753984006212631892[7] = 0;
   out_1753984006212631892[8] = 0;
}
void h_31(double *state, double *unused, double *out_3395966988892798249) {
   out_3395966988892798249[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3838464682337482083) {
   out_3838464682337482083[0] = 0;
   out_3838464682337482083[1] = 0;
   out_3838464682337482083[2] = 0;
   out_3838464682337482083[3] = 0;
   out_3838464682337482083[4] = 0;
   out_3838464682337482083[5] = 0;
   out_3838464682337482083[6] = 0;
   out_3838464682337482083[7] = 0;
   out_3838464682337482083[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_4523861128599971785) {
  err_fun(nom_x, delta_x, out_4523861128599971785);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3940455236356545429) {
  inv_err_fun(nom_x, true_x, out_3940455236356545429);
}
void car_H_mod_fun(double *state, double *out_1374868943770561080) {
  H_mod_fun(state, out_1374868943770561080);
}
void car_f_fun(double *state, double dt, double *out_1405568563655631313) {
  f_fun(state,  dt, out_1405568563655631313);
}
void car_F_fun(double *state, double dt, double *out_2452143806039032916) {
  F_fun(state,  dt, out_2452143806039032916);
}
void car_h_25(double *state, double *unused, double *out_1023489145526815441) {
  h_25(state, unused, out_1023489145526815441);
}
void car_H_25(double *state, double *unused, double *out_3807818720460521655) {
  H_25(state, unused, out_3807818720460521655);
}
void car_h_24(double *state, double *unused, double *out_5500848379716595858) {
  h_24(state, unused, out_5500848379716595858);
}
void car_H_24(double *state, double *unused, double *out_4967073687351649239) {
  H_24(state, unused, out_4967073687351649239);
}
void car_h_30(double *state, double *unused, double *out_6431998359533457045) {
  h_30(state, unused, out_6431998359533457045);
}
void car_H_30(double *state, double *unused, double *out_7722235011757413206) {
  H_30(state, unused, out_7722235011757413206);
}
void car_h_26(double *state, double *unused, double *out_516367605799594709) {
  h_26(state, unused, out_516367605799594709);
}
void car_H_26(double *state, double *unused, double *out_66315401586465431) {
  H_26(state, unused, out_66315401586465431);
}
void car_h_27(double *state, double *unused, double *out_6411654288901885372) {
  h_27(state, unused, out_6411654288901885372);
}
void car_H_27(double *state, double *unused, double *out_8549745750151713499) {
  H_27(state, unused, out_8549745750151713499);
}
void car_h_29(double *state, double *unused, double *out_6136460226617379483) {
  h_29(state, unused, out_6136460226617379483);
}
void car_H_29(double *state, double *unused, double *out_7212003667443021022) {
  H_29(state, unused, out_7212003667443021022);
}
void car_h_28(double *state, double *unused, double *out_8791825661536103721) {
  h_28(state, unused, out_8791825661536103721);
}
void car_H_28(double *state, double *unused, double *out_1753984006212631892) {
  H_28(state, unused, out_1753984006212631892);
}
void car_h_31(double *state, double *unused, double *out_3395966988892798249) {
  h_31(state, unused, out_3395966988892798249);
}
void car_H_31(double *state, double *unused, double *out_3838464682337482083) {
  H_31(state, unused, out_3838464682337482083);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
