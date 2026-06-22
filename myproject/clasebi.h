#pragma once
#include <iostream>
#include <string>

// საბაზო კლასი Employee
// ყველა თანამშრომელი ამ კლასიდან მემკვიდრეობით მიიღებს საერთო ველებს
class Employee {
public:
    Employee(double id = 0, const std::string& name = "", double base_salary = 0, double exp = 0)
        : id(id), name(name), salary(0), exp(exp)
    {
    }

    // ხელფასის გამოთვლის ზოგადი ფორმულა
    virtual double cal_salary(double base_salary) const {
        return base_salary + exp * 100;
    }

    // operator<< საშუალებას გვაძლევს ობიექტი cout-ით დავბეჭდოთ
    friend std::ostream& operator<<(std::ostream& out, const Employee& emp) {
        emp.Display(out);
        return out;
    }

    // pure virtual ფუნქციები
    // ამიტომ Employee არის abstract class
    virtual double get_salary() const = 0;
    virtual double get_exp() const = 0;
    virtual std::string get_name() const = 0;
    virtual void Display(std::ostream& out) const = 0;

    // virtual destructor საჭიროა,
    // რადგან შვილობილი ობიექტები base pointer-ით იშლება
    virtual ~Employee() = default;

protected:
    double id;
    double salary;
    double exp;
    std::string name;
};

// Tester კლასი
class tester : public Employee {
private:
    std::string level;

public:
    tester(double id=0, const std::string& name='', double base_salary=0, double exp=0, const std::string& lvl='')
        : Employee(id, name, base_salary, exp), level(lvl)
    {
        salary = cal_salary(base_salary);
    }

    std::string get_name() const override {
        return name;
    }

    double get_salary() const override {
        return salary;
    }

    double get_exp() const override {
        return exp;
    }

    void Display(std::ostream& out) const override {
        out << "Tester: "
            << "ID: " << id
            << ", Name: " << name
            << ", Salary: " << salary
            << ", Experience: " << exp
            << ", Level: " << level;
    }

    double cal_salary(double base) const override {
        if (level == "Senior")
            return base * 3 + exp * 10;
        else if (level == "Middle")
            return base * 2 + exp * 10;
        else
            return base + exp * 10;
    }
};

// CIO კლასი
class CIO : public Employee {
public:
    CIO(double id=0, const std::string& name='', double base_salary=0, double exp=0)
        : Employee(id, name, base_salary, exp)
    {
        salary = cal_salary(base_salary);
    }

    std::string get_name() const override {
        return name;
    }

    double get_salary() const override {
        return salary;
    }

    double get_exp() const override {
        return exp;
    }

    void Display(std::ostream& out) const override {
        out << "CIO: "
            << "ID: " << id
            << ", Name: " << name
            << ", Salary: " << salary
            << ", Experience: " << exp;
    }

    double cal_salary(double base) const override {
        return base + exp * 100;
    }
};

// PR Manager კლასი
class pr_man : public Employee {
public:
    pr_man(double id=0, const std::string& name='', double base_salary=0, double exp=0)
        : Employee(id, name, base_salary, exp)
    {
        salary = cal_salary(base_salary);
    }

    std::string get_name() const override {
        return name;
    }

    double get_salary() const override {
        return salary;
    }

    double get_exp() const override {
        return exp;
    }

    void Display(std::ostream& out) const override {
        out << "PR Manager: "
            << "ID: " << id
            << ", Name: " << name
            << ", Salary: " << salary
            << ", Experience: " << exp;
    }

    double cal_salary(double base) const override {
        return base + exp * 10;
    }
};

// Developer საბაზო კლასი
class Developer : public Employee {
protected:
    std::string level;

public:
    Developer(double id = 0, const std::string& name = "", double base_salary = 0, double exp = 0, const std::string& lvl = "")
        : Employee(id, name, base_salary, exp), level(lvl)
    {
        salary = cal_salary(base_salary);
    }

    virtual double cal_salary(double base_salary) const override {
        return base_salary + exp * 100;
    }
};

// Backend Developer კლასი
class backend : public Developer {
private:
    std::string tec;

public:
    backend(double id = 0, const std::string& name = "", double base_salary = 0, double exp = 0,
        const std::string& lvl = "", const std::string& tec = "")
        : Developer(id, name, base_salary, exp, lvl), tec(tec)
    {
        salary = cal_salary(base_salary);
    }

    std::string get_name() const override {
        return name;
    }

    double get_salary() const override {
        return salary;
    }

    double get_exp() const override {
        return exp;
    }

    void Display(std::ostream& out) const override {
        out << "Backend Developer: "
            << "ID: " << id
            << ", Name: " << name
            << ", Salary: " << salary
            << ", Experience: " << exp
            << ", Level: " << level
            << ", Technology: " << tec;
    }

    double cal_salary(double base) const override {
        if (tec == ".Net") {
            if (level == "Senior")
                return base * 3 + exp * 10;
            else if (level == "Middle")
                return base * 2 + exp * 10;
            else
                return base + exp * 10;
        }

        if (tec == ".Spring") {
            if (level == "Senior")
                return base * 3.5 + exp * 10;
            else if (level == "Middle")
                return base * 2.5 + exp * 10;
            else
                return base + exp * 10;
        }

        if (tec == ".Django") {
            if (level == "Senior")
                return base * 3.55 + exp * 10;
            else if (level == "Middle")
                return base * 2.55 + exp * 10;
            else
                return base + exp * 10;
        }

        return base + exp * 10;
    }
};

// Frontend Developer კლასი
class frontend : public Developer {
private:
    std::string tec;

public:
    frontend(double id = 0, const std::string& name = "", double base_salary = 0, double exp = 0,
        const std::string& lvl = "", const std::string& tec = "")
        : Developer(id, name, base_salary, exp, lvl), tec(tec)
    {
        salary = cal_salary(base_salary);
    }

    std::string get_name() const override {
        return name;
    }

    double get_salary() const override {
        return salary;
    }

    double get_exp() const override {
        return exp;
    }

    void Display(std::ostream& out) const override {
        out << "Frontend Developer: "
            << "ID: " << id
            << ", Name: " << name
            << ", Salary: " << salary
            << ", Experience: " << exp
            << ", Level: " << level
            << ", Technology: " << tec;
    }

    double cal_salary(double base) const override {
        if (tec == "Angular") {
            if (level == "Senior")
                return base * 3 + exp * 10;
            else if (level == "Middle")
                return base * 2 + exp * 10;
            else
                return base + exp * 10;
        }

        if (tec == "React") {
            if (level == "Senior")
                return base * 3 + exp * 10;
            else if (level == "Middle")
                return base * 2 + exp * 10;
            else
                return base + exp * 10;
        }

        if (tec == "Vue") {
            if (level == "Senior")
                return base * 3 + exp * 10;
            else if (level == "Middle")
                return base * 2 + exp * 10;
            else
                return base + exp * 10;
        }

        return base + exp * 10;
    }
};

// Engineer საბაზო კლასი
class enginer : public Employee {
protected:
    std::string level;

public:
    enginer(double id = 0, const std::string& name = "", double base_salary = 0, double exp = 0, const std::string& lvl = "")
        : Employee(id, name, base_salary, exp), level(lvl)
    {
        salary = cal_salary(base_salary);
    }

    virtual double cal_salary(double base_salary) const override {
        return base_salary + exp * 100;
    }
};

// DevOps კლასი
class DevOps : public enginer {
public:
    DevOps(double id = 0, const std::string& name = "", double base_salary = 0, double exp = 0,
        const std::string& lvl = "", const std::string& tec = "")
        : enginer(id, name, base_salary, exp, lvl)
    {
        salary = cal_salary(base_salary);
    }

    std::string get_name() const override {
        return name;
    }

    double get_salary() const override {
        return salary;
    }

    double get_exp() const override {
        return exp;
    }

    void Display(std::ostream& out) const override {
        out << "DevOps: "
            << "ID: " << id
            << ", Name: " << name
            << ", Salary: " << salary
            << ", Experience: " << exp
            << ", Level: " << level;
    }

    double cal_salary(double base) const override {
        if (level == "Senior")
            return base * 3 + exp * 10;
        else if (level == "Middle")
            return base * 2 + exp * 10;
        else
            return base + exp * 10;
    }
};

// DataBase Engineer კლასი
class DataBase : public enginer {
public:
    DataBase(double id = 0, const std::string& name = "", double base_salary = 0, double exp = 0,
        const std::string& lvl = "", const std::string& tec = "")
        : enginer(id, name, base_salary, exp, lvl)
    {
        salary = cal_salary(base_salary);
    }

    std::string get_name() const override {
        return name;
    }

    double get_salary() const override {
        return salary;
    }

    double get_exp() const override {
        return exp;
    }

    void Display(std::ostream& out) const override {
        out << "DataBase Engineer: "
            << "ID: " << id
            << ", Name: " << name
            << ", Salary: " << salary
            << ", Experience: " << exp
            << ", Level: " << level;
    }

    double cal_salary(double base) const override {
        if (level == "Senior")
            return base * 3 + exp * 10;
        else if (level == "Middle")
            return base * 2 + exp * 10;
        else
            return base + exp * 10;
    }
};