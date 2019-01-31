#ifndef AVM_IOPERAND_HPP
#define AVM_IOPERAND_HPP

#include <iostream>
#include <string>

enum eOperandType {Int8, Int16, Int32, Float, Double};

class IOperand {

public:

	virtual int				getPrecision() const = 0;
	virtual eOperandType	getType() const = 0;

	virtual IOperand const * operator+(IOperand const & rhs) const = 0;
	virtual IOperand const * operator-(IOperand const & rhs) const = 0;
	virtual IOperand const * operator*(IOperand const & rhs) const = 0;
	virtual IOperand const * operator/(IOperand const & rhs) const = 0;
	virtual IOperand const * operator%(IOperand const & rhs) const = 0;

	virtual std::string const & toString() const = 0;
	
	virtual ~IOperand() {}
};

#endif