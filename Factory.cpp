#include "Factory.hpp"
#include "Operand.hpp"

Factory::Factory() {

	_vecOfFunc.push_back(&Factory::createInt8);
	_vecOfFunc.push_back(&Factory::createInt16);
	_vecOfFunc.push_back(&Factory::createInt32);
	_vecOfFunc.push_back(&Factory::createFloat);
	_vecOfFunc.push_back(&Factory::createDouble);
}

IOperand const * 
Factory::createOperand(eOperandType type, std::string const & value) const {

//	IOperand const* (Factory::*f)(std::string const & value) const;
//	funcPtr f = _vecOfFunc[type];
	return (this->*_vecOfFunc[type])(value);
}

IOperand const *
Factory::createInt8(std::string const & value) const {

	std::cout<< "int8" << std::endl;
	/////////
	return new Operand<int8_t>(value, Int8, this);

}

IOperand const *
Factory::createInt16(std::string const & value) const {

	std::cout<< "int16" << std::endl;
	return new Operand<int16_t>(value, Int16, this);
}

IOperand const *
Factory::createInt32(std::string const & value) const {

	std::cout<< "int32" << std::endl;
	return new Operand<int32_t>(value, Int32, this);
}

IOperand const *
Factory::createFloat(std::string const & value) const {

	std::cout<< "float" << std::endl;
	return new Operand<float>(value, Float, this);
}

IOperand const *
Factory::createDouble(std::string const & value) const {

	std::cout<< "double" << std::endl;
	return new Operand<double>(value, Double, this);
}