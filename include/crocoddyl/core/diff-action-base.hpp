///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2018-2019, LAAS-CNRS
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#ifndef CROCODDYL_CORE_DIFF_ACTION_BASE_HPP_
#define CROCODDYL_CORE_DIFF_ACTION_BASE_HPP_

#include "crocoddyl/core/action-base.hpp"

namespace crocoddyl {

struct DifferentialActionDataAbstract;  // forward declaration

class DifferentialActionModelAbstract {
 public:
  DifferentialActionModelAbstract(const unsigned int& nq, const unsigned int& nv, const unsigned int& nu);
  virtual ~DifferentialActionModelAbstract();

  virtual void calc(std::shared_ptr<DifferentialActionDataAbstract>& data, const Eigen::Ref<const Eigen::VectorXd>& x,
                    const Eigen::Ref<const Eigen::VectorXd>& u) = 0;
  virtual void calcDiff(std::shared_ptr<DifferentialActionDataAbstract>& data,
                        const Eigen::Ref<const Eigen::VectorXd>& x, const Eigen::Ref<const Eigen::VectorXd>& u,
                        const bool& recalc = true) = 0;
  virtual std::shared_ptr<DifferentialActionDataAbstract> createData() = 0;

  void calc(std::shared_ptr<DifferentialActionDataAbstract>& data, const Eigen::Ref<const Eigen::VectorXd>& x);
  void calcDiff(std::shared_ptr<DifferentialActionDataAbstract>& data, const Eigen::Ref<const Eigen::VectorXd>& x);

  unsigned int get_nq() const;
  unsigned int get_nv() const;
  unsigned int get_nu() const;
  unsigned int get_nx() const;
  unsigned int get_ndx() const;
  unsigned int get_nout() const;
  unsigned int get_ncost() const;

 protected:
  unsigned int nq_;
  unsigned int nv_;
  unsigned int nu_;
  unsigned int nx_;
  unsigned int ndx_;
  unsigned int nout_;
  unsigned int ncost_;
  Eigen::VectorXd unone_;
};

struct DifferentialActionDataAbstract {
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  template <typename Model>
  DifferentialActionDataAbstract(Model* const model) {
    const int& ndx = model->get_ndx();
    const int& nu = model->get_nu();
    const int& nout = model->get_nout();
    const int& ncost = model->get_ncost();
    xout = Eigen::VectorXd::Zero(nout);
    Fx = Eigen::MatrixXd::Zero(nout, ndx);
    Fu = Eigen::MatrixXd::Zero(nout, nu);
    Lx = Eigen::VectorXd::Zero(ndx);
    Lu = Eigen::VectorXd::Zero(nu);
    Lxx = Eigen::MatrixXd::Zero(ndx, ndx);
    Lxu = Eigen::MatrixXd::Zero(ndx, nu);
    Luu = Eigen::MatrixXd::Zero(nu, nu);
    r = Eigen::VectorXd::Zero(ncost);
    Rx = Eigen::MatrixXd::Zero(ncost, ndx);
    Ru = Eigen::MatrixXd::Zero(ncost, nu);
  }

  const double& get_cost() const { return cost; }
  const Eigen::VectorXd& get_xout() const { return xout; }
  const Eigen::VectorXd& get_Lx() const { return Lx; }
  const Eigen::VectorXd& get_Lu() const { return Lu; }
  const Eigen::MatrixXd& get_Lxx() const { return Lxx; }
  const Eigen::MatrixXd& get_Lxu() const { return Lxu; }
  const Eigen::MatrixXd& get_Luu() const { return Luu; }
  const Eigen::MatrixXd& get_Fx() const { return Fx; }
  const Eigen::MatrixXd& get_Fu() const { return Fu; }
  const Eigen::VectorXd& get_r() const { return r; }
  const Eigen::MatrixXd& get_Rx() const { return Rx; }
  const Eigen::MatrixXd& get_Ru() const { return Ru; }

  double cost;
  Eigen::VectorXd xout;
  Eigen::MatrixXd Fx;
  Eigen::MatrixXd Fu;
  Eigen::VectorXd Lx;
  Eigen::VectorXd Lu;
  Eigen::MatrixXd Lxx;
  Eigen::MatrixXd Lxu;
  Eigen::MatrixXd Luu;
  Eigen::VectorXd r;
  Eigen::MatrixXd Rx;
  Eigen::MatrixXd Ru;
};

}  // namespace crocoddyl

#endif  // CROCODDYL_CORE_DIFF_ACTION_BASE_HPP_
