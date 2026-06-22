
#pragma once
#include <iostream>
class Employee {
public:
	Employee(double id = 0, std::string name = "", double base_salary = 0, double exp = 0) :
		id(id), name(name), salary(0), exp(exp) {
	}
	virtual double cal_salary(double base_salary) const {
		return base_salary + exp * 100;
	}

	friend std::ostream& operator<<(std::ostream& out, const Employee& emp) {
		emp.Display(out);
		return out;
	}
	virtual double get_salary() const = 0;
	virtual double get_exp() const = 0;
	virtual std::string get_name() const = 0;
	virtual void Display(std::ostream&) const = 0;
	virtual ~Employee() = default;
protected:
	double id, salary, exp;
	std::string name;
};
inline std::ostream& operator<<(std::ostream& out, const Employee& emp)
{
	emp.Display(out);
	return out;
};
class tester :public Employee {
	std::string level;
public:
	tester(double id, std::string name, double base_salary, double exp, std::string lvl)
		:Employee(id, name, base_salary, exp), level(lvl) {
		salary = cal_salary(base_salary);
	}
	std::string get_name()const override { return name; }
	double get_salary()const override { return salary; }
	double get_exp()const override { return exp; }

	void Display(std::ostream& out)const override {
		out << id << " " << name << " " << salary << " " << exp << " " << level;
	}
	friend std::ostream& operator<<(std::ostream&, const Employee&);
	double cal_salary(double base)const override {
		if (level == "Senior") return base * 3 + exp * 10;
		else if (level == "Middle") return base * 2 + exp * 10;
		else return base + exp * 10;
	}

};
class CIO :public Employee {
public:
	CIO(double id, std::string name, double base_salary, double exp)
		:Employee(id, name, base_salary, exp) {
		salary = cal_salary(base_salary);
	}
	std::string get_name()const override { return name; }
	double get_salary()const override { return salary; }
	double get_exp()const override { return exp; }
	void Display(std::ostream& out)const override {
		out << id << " " << name << " " << salary << " " << exp;
	}

	double cal_salary(double base)const override {
		return  base + exp * 100;
	}
};
class pr_man :public Employee {
public:
	pr_man(double id, std::string name, double base_salary, double exp)
		:Employee(id, name, base_salary, exp) {
		salary = cal_salary(base_salary);
	}
	std::string get_name()const override { return name; }
	double get_salary()const override { return salary; }
	double get_exp()const override { return exp; }
	void Display(std::ostream& out)const override {
		out << id << " " << name << " " << salary << " " << exp;
	}

	double cal_salary(double base)const override {
		return  base + exp * 10;
	}
};
class Developer :public Employee {
protected:
	std::string level;
public:
	Developer(double id = 0, std::string name = "", double base_salary = 0, double exp = 0, std::string lvl)
		: Employee(id, name, base_salary, exp), level(lvl)
	{
		salary = cal_salary(base_salary);
	}
	virtual double cal_salary(double base_salary) const override {
		return base_salary + exp * 100;
	}
	virtual double get_salary() const override = 0;
	virtual double get_exp() const override = 0;
	virtual std::string get_name() const override = 0;
	virtual void Display(std::ostream&) const override = 0;
};
class backend :public Developer {
	std::string tec;
public:
	backend(double id = 0, std::string name = "", double base_salary = 0, double exp = 0, std::string lvl, std::string tec)
		: Developer(id, name, base_salary, exp, lvl), tec(tec)
	{
		salary = cal_salary(base_salary);
	}
	std::string get_name()const override { return name; }
	double get_salary()const override { return salary; }
	double get_exp()const override { return exp; }
	void Display(std::ostream& out)const override {
		out << id << " " << name << " " << salary << " " << exp << " " << level << " " << tec;
	}

	double cal_salary(double base)const override {
		if (tec == ".Net") {
			if (level == "Senior") return base * 3 + exp * 10;
			else if (level == "Middle") return base * 2 + exp * 10;
			else return base + exp * 10;
		}
		if (tec == ".Spring") {
			if (level == "Senior") return base * 3.5 + exp * 10;
			else if (level == "Middle") return base * 2.5 + exp * 10;
			else return base + exp * 10;
		}
		if (tec == ".Django") {
			if (level == "Senior") return base * 3.55 + exp * 10;
			else if (level == "Middle") return base * 2.55 + exp * 10;
			else return base + exp * 10;
		}
		return base + exp * 10;
	}
};
class frontend :public Developer {
	std::string tec;
public:
	frontend(double id = 0, std::string name = "", double base_salary = 0, double exp = 0, std::string lvl, std::string tec)
		: Developer(id, name, base_salary, exp, lvl), tec(tec)
	{
		salary = cal_salary(base_salary);
	}
	std::string get_name()const override { return name; }
	double get_salary()const override { return salary; }
	double get_exp()const override { return exp; }
	void Display(std::ostream& out)const override {
		out << id << " " << name << " " << salary << " " << exp << " " << level << " " << tec;
	}

	double cal_salary(double base)const override {
		if (tec == "Angular") {
			if (level == "Senior") return base * 3 + exp * 10;
			else if (level == "Middle") return base * 2 + exp * 10;
			else return base + exp * 10;
		}
		if (tec == "React") {
			if (level == "Senior") return base * 3 + exp * 10;
			else if (level == "Middle") return base * 2 + exp * 10;
			else return base + exp * 10;
		}
		if (tec == "Vue") {
			if (level == "Senior") return base * 3 + exp * 10;
			else if (level == "Middle") return base * 2 + exp * 10;
			else return base + exp * 10;
		}
		return base + exp * 10;
	}
};
class enginer :public Employee {
protected:
	std::string level;
public:
	enginer(double id = 0, std::string name = "", double base_salary = 0, double exp = 0, std::string lvl)
		: Employee(id, name, base_salary, exp), level(lvl)
	{
		salary = cal_salary(base_salary);
	}
	virtual double cal_salary(double base_salary) const override {
		return base_salary + exp * 100;
	}
	virtual double get_salary() const override = 0;
	virtual double get_exp() const override = 0;
	virtual std::string get_name() const override = 0;
	virtual void Display(std::ostream&) const override = 0;
};
class DevOps :public enginer {
public:
	DevOps(double id = 0, std::string name = "", double base_salary = 0, double exp = 0, std::string lvl, std::string tec)
		: enginer(id, name, base_salary, exp, lvl)
	{
		salary = cal_salary(base_salary);
	}
	std::string get_name()const override { return name; }
	double get_salary()const override { return salary; }
	double get_exp()const override { return exp; }
	void Display(std::ostream& out)const override {
		out << id << " " << name << " " << salary << " " << exp << " " << level;
	}

	double cal_salary(double base)const override {
		if (level == "Senior") return base * 3 + exp * 10;
		else if (level == "Middle") return base * 2 + exp * 10;
		else return base + exp * 10;
	}
};
class DataBase :public enginer {
public:
	DataBase(double id = 0, std::string name = "", double base_salary = 0, double exp = 0, std::string lvl, std::string tec)
		: enginer(id, name, base_salary, exp, lvl)
	{
		salary = cal_salary(base_salary);
	}
	std::string get_name()const override { return name; }
	double get_salary()const override { return salary; }
	double get_exp()const override { return exp; }
	void Display(std::ostream& out)const override {
		out << id << " " << name << " " << salary << " " << exp << " " << level;
	}

	double cal_salary(double base)const override {
		if (level == "Senior") return base * 3 + exp * 10;
		else if (level == "Middle") return base * 2 + exp * 10;
		else return base + exp * 10;
	}
};


