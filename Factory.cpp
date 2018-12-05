#include "Factory.hpp"

Factory::Factory() {

	_vecOfFunc.push_back(&Factory::createInt8);
	_vecOfFunc.push_back(&Factory::createInt16);
	_vecOfFunc.push_back(&Factory::createInt32);
	_vecOfFunc.push_back(&Factory::createFloat);
	_vecOfFunc.push_back(&Factory::createDouble);
}

IOperand const * 
Factory::createOperand(eOperandType type, std::string const & value) const {

	return _vecOfFunc[type](value);
}

IOperand const *
Factory::createInt8(std::string const & value) const {

	std::cout<< "int8" << std::endl;
	/////////
	return new Operand<int8_t>(value, eInt8);

}

IOperand const *
Factory::createInt16(std::string const & value) const {

	std::cout<< "int16" << std::endl;
	return new Operand<int16_t>(value, eInt16);
}

IOperand const *
Factory::createInt32(std::string const & value) const {

	std::cout<< "int32" << std::endl;
	return new Operand<int32_t>(value, eInt32);
}

IOperand const *
Factory::createFloat(std::string const & value) const {

	std::cout<< "float" << std::endl;
	return new Operand<float>(value, eFloat);
}

IOperand const *
Factory::createDouble(std::string const & value) const {

	std::cout<< "double" << std::endl;
	return new Operand<double>(value, eDouble);
}