#ifndef ACTIONS_H
#define ACTIONS_H

#include "Objects.h"
class Validator;

#include <string>
#include <vector>


struct Action {
  virtual void validate(Validator*) const = 0;
};

struct CookAction: public Action {
  std::string  noodle;
  unsigned int pot_id;

  void validate(Validator*) const;
  CookAction(unsigned int pot_id, const std::string& noodle) {
    this->noodle = noodle;
    this->pot_id = pot_id;
  }
};

struct CleanAction: public Action {
  unsigned int pot_id;

  void validate(Validator*) const;
  CleanAction(unsigned int pot_id) {
    this->pot_id = pot_id;
  }
};

struct NoAction: public Action {
  void validate(Validator*) const;
};

struct ServeAction: public Action {
  std::vector<Serve> serves;

  void validate(Validator*) const;
  ServeAction(const std::vector<Serve>& serves) {
    this->serves = serves;
  }
};

#endif
