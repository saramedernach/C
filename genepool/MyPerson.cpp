#include "MyPerson.h"


MyPerson::MyPerson(const string name, const Gender gender, MyPerson* mother, MyPerson* father, set<MyPerson*> children) {

    mName = name;
    mGender = gender;
    mMother = mother;
    mFather = father;
    mChildren = children;

}

const string& MyPerson::name()  const {

    return mName;

}

Gender MyPerson::gender() const {

    return mGender;

}

MyPerson* MyPerson::mother() {

    return mMother;

}

MyPerson* MyPerson::father() {

    return mFather;

}

set<Person*> MyPerson::ancestors(PMod pmod) {

    set<Person*> s;
    
    for (Person* person: parents(pmod)) {

        s.insert(person);
        ancestorRecursion(person, s);

    }

    return s;

}

set<Person*> MyPerson::aunts(PMod pmod, SMod smod) {

    set<Person*> s;

    for (Person* parent: parents(pmod)) {

        for (Person* aunt: parent->sisters(PMod::ANY, smod)) {

            s.insert(aunt);

        }

    }

    return s;

}

set<Person*> MyPerson::brothers(PMod pmod, SMod smod) {

    set<Person*> s;
    for (Person* person: siblings(pmod, smod)) {

        if (person->gender() == Gender::MALE) {

            s.insert(person);

        }

    }
    
    return s;

}

set<Person*> MyPerson::children() {

    set<Person*> s;
    for (Person* person: mChildren) {

        s.insert(person);

    }

    return s;

}

set<Person*> MyPerson::cousins(PMod pmod, SMod smod) {

    set<Person*> s;

    for (Person* parent: parents(pmod)) {

        for (Person* sibling: parent->siblings(PMod::ANY, smod)) {

            for (Person* cousin: sibling->children()) {

                s.insert(cousin);

            }

        }

    }

    return s;

}

set<Person*> MyPerson::daughters() {

    set<Person*> s;
    for (Person* person: mChildren) {

        if (person->gender() == Gender::FEMALE) {

            s.insert(person);

        }

    }

    return s;

}

set<Person*> MyPerson::descendants() {

    set<Person*> s;

    descendantRecursion(this, s);

    return s;

}

void MyPerson::descendantRecursion(Person* person, std::set<Person*> &s) {

    if (!children().empty()) {

        for (Person* person: children()) {

            s.insert(person);
            descendantRecursion(person, s);

        }

    }

}

set<Person*> MyPerson::grandchildren() {

    set<Person*> s;
    for (Person* child: children()) {

        for (Person* grandchild: child->children()) {

            s.insert(grandchild);

        }

    }

    return s;

}

set<Person*> MyPerson::granddaughters() {

    set<Person*> s;
    for (Person* person: grandchildren()) {

        if (person->gender() == Gender::FEMALE) {

            s.insert(person);

        }

    }

    return s;

}

set<Person*> MyPerson::grandfathers(PMod pmod) {

    set<Person*> s;

    for (Person* person: grandparents(pmod)) {

        if (person->gender() == Gender::MALE) {

            s.insert(person);

        }

    }

    return s;

}

set<Person*> MyPerson::grandmothers(PMod pmod) {

    set<Person*> s;

    for (Person* person: grandparents(pmod)) {

        if (person->gender() == Gender::FEMALE) {

            s.insert(person);

        }

    }

    return s;

}

set<Person*> MyPerson::grandparents(PMod pmod) {

    set<Person*> s;

    for (Person* parent: parents(pmod)) {

        for (Person* grandparent: parent->parents()) {

            s.insert(grandparent);

        }

    }

    return s;

}

set<Person*> MyPerson::grandsons() {

    set<Person*> s;
    for (Person* person: grandchildren()) {

        if (person->gender() == Gender::MALE) {

            s.insert(person);

        }

    }

    return s;

}

set<Person*> MyPerson::nephews(PMod pmod, SMod smod) {

    set<Person*> s;

    for (Person* sibling: siblings(pmod, smod)) {

        for (Person* nephew: sibling->sons()) {

            s.insert(nephew);

        }

    }

    return s;

}

set<Person*> MyPerson::nieces(PMod pmod, SMod smod) {

    set<Person*> s;

    for (Person* sibling: siblings(pmod, smod)) {

        for (Person* niece: sibling->daughters()) {

            s.insert(niece);

        }

    }

    return s;

}

set<Person*> MyPerson::parents(PMod pmod) {

    set<Person*> s;

    if (pmod == PMod::MATERNAL) {

        if (mother() == nullptr) {

            return s;

        }

        s.insert(mother());

    }
    else if (pmod == PMod::PATERNAL) {

        if (father() == nullptr) {

            return s;

        }

        s.insert(father());
        
    }
    else {

        if (mother() == nullptr && father() == nullptr) {

            return s;

        }
        else if (mother() == nullptr && father() != nullptr) {

            s.insert(father());

        }
        else if (mother() != nullptr && father() == nullptr) {

            s.insert(mother());

        }
        else {

            s.insert(mother());
            s.insert(father());

        }

    }

    return s;

}

set<Person*> MyPerson::siblings(PMod pmod, SMod smod) {

    set<Person*> s;

    for (Person* parent: parents(pmod)) {

        for (Person* sibling: parent->children()) {

            if (sibling == this) {

                continue;

            }

            if (smod == SMod::FULL) {

                if (mother() == sibling->mother() && father() == sibling->father()) {

                    s.insert(sibling);

                }

            }
            else if (smod == SMod::HALF) {

                if (mother() == sibling->mother() && father() != sibling->father()) {

                    s.insert(sibling);

                }

                if (mother() != sibling->mother() && father() == sibling->father()) {

                    s.insert(sibling);

                }
                
            }
            else {

                s.insert(sibling);

            }

        }

    }

    return s;

}

set<Person*> MyPerson::sisters(PMod pmod, SMod smod) {

    set<Person*> s;
    for (Person* person: siblings(pmod, smod)) {

        if (person->gender() == Gender::FEMALE) {

            s.insert(person);

        }

    }
    
    return s;

}

set<Person*> MyPerson::sons() {

    set<Person*> s;
    for (Person* person: mChildren) {

        if (person->gender() == Gender::MALE) {

            s.insert(person);

        }

    }

    return s;

}

set<Person*> MyPerson::uncles(PMod pmod, SMod smod) {

    set<Person*> s;

    for (Person* parent: parents(pmod)) {

        for (Person* uncle: parent->brothers(PMod::ANY, smod)) {

            s.insert(uncle);

        }

    }

    return s;

}

void MyPerson::ancestorRecursion(Person* person, std::set<Person*> &s) {

    if (person != nullptr) {

        s.insert(person);
        ancestorRecursion(person->mother(), s);
        ancestorRecursion(person->father(), s);

    }

}

void MyPerson::addChild(MyPerson* person) {

  mChildren.insert(person);

}
