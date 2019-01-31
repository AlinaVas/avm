#pragma once

#include <iostream>
#include <string>

enum eOperandType {Int8, Int16, Int32, Float, Double};

class IOperand {

public:

	virtual int				getPrecision() const = 0; // Precision of the commandType of the instance
	virtual eOperandType	getType() const = 0;  // Type of the instance

	virtual IOperand const * operator+(IOperand const & rhs) const = 0;
	virtual IOperand const * operator-(IOperand const & rhs) const = 0;
	virtual IOperand const * operator*(IOperand const & rhs) const = 0;
	virtual IOperand const * operator/(IOperand const & rhs) const = 0;
	virtual IOperand const * operator%(IOperand const & rhs) const = 0;

	virtual std::string const & toString() const = 0; // String representation of the instance
	
	virtual ~IOperand() {}
};