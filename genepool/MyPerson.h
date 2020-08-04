#ifndef MYPERSON_H
#define MYPERSON_H

#include "Person.h"

using namespace std;

class MyPerson: public Person {
  
  string mName;
  Gender mGender;
  MyPerson* mMother;
  MyPerson* mFather;
  set<MyPerson*> mChildren;

public:
  
  MyPerson(const string name, const Gender gender, MyPerson* mother, MyPerson* father, set<MyPerson*> children);
  //~MyPerson();

  // Required Functions
  const std::string& name()   const;
  Gender             gender() const;
  MyPerson*          mother();
  MyPerson*          father();

  // Required Relationship Functions
  set<Person*> ancestors(PMod pmod = PMod::ANY);
  set<Person*> aunts(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  set<Person*> brothers(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  set<Person*> children();
  set<Person*> cousins(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  set<Person*> daughters();
  set<Person*> descendants();
  set<Person*> grandchildren();
  set<Person*> granddaughters();
  set<Person*> grandfathers(PMod pmod = PMod::ANY);
  set<Person*> grandmothers(PMod pmod = PMod::ANY);
  set<Person*> grandparents(PMod pmod = PMod::ANY);
  set<Person*> grandsons();
  set<Person*> nephews(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  set<Person*> nieces(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  set<Person*> parents(PMod pmod = PMod::ANY);
  set<Person*> siblings(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  set<Person*> sisters(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  set<Person*> sons();
  set<Person*> uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);

  // Other Member Functions
  void ancestorRecursion(Person* person, std::set<Person*> &s);
  void descendantRecursion(Person* person, std::set<Person*> &s);
  void addChild(MyPerson* person);

};

#endif
