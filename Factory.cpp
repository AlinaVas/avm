#include "Factory.hpp"
#include "Operand.hpp"
#include <limits>

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

    auto val = std::stold(value);
    if (val < std::numeric_limits<int8_t>::min() || val > std::numeric_limits<int8_t>::max())
        throw ValueOutOfRangeException("value overflow (int8_t)");
	return new Operand<int8_t>(value, Int8, this);

}

IOperand const *
Factory::createInt16(std::string const & value) const {

	auto val = std::stold(value);
	if (val < std::numeric_limits<int16_t>::min() || val > std::numeric_limits<int16_t>::max())
		throw ValueOutOfRangeException("value overflow (int16_t)");
	return new Operand<int16_t>(value, Int16, this);
}

IOperand const *
Factory::createInt32(std::string const & value) const {

	auto val = std::stold(value);
	if (val < std::numeric_limits<int32_t>::min() || val > std::numeric_limits<int32_t>::max())
		throw ValueOutOfRangeException("value overflow (int32_t)");
	return new Operand<int32_t>(value, Int32, this);
}

IOperand const *
Factory::createFloat(std::string const & value) const {

	auto val = std::stold(value);
	if (val < -std::numeric_limits<float>::max() || val > std::numeric_limits<float>::max())
		throw ValueOutOfRangeException("value overflow (float)");
	if (val < std::numeric_limits<float>::min())
		throw ValueOutOfRangeException("value underflow (float)");
	return new Operand<float>(value, Float, this);
}

IOperand const *
Factory::createDouble(std::string const & value) const {

	auto val = std::stold(value);
	if (val < -std::numeric_limits<double>::max() || val > std::numeric_limits<double>::max())
		throw ValueOutOfRangeException("value overflow (double)");
	if (val < std::numeric_limits<double>::min())
		throw ValueOutOfRangeException("value underflow (double)");
	return new Operand<double>(value, Double, this);
}

/************************ EXCEPTIONS ****************************/

Factory::ValueOutOfRangeException::ValueOutOfRangeException(char const *msg) noexcept : _msg(msg) {}

Factory::ValueOutOfRangeException::ValueOutOfRangeException(ValueOutOfRangeException const &rhs) noexcept {
	*this = rhs;
}

Factory::ValueOutOfRangeException::~ValueOutOfRangeException() = default;

Factory::ValueOutOfRangeException
&Factory::ValueOutOfRangeException::operator=(Factory::ValueOutOfRangeException const &rhs) noexcept {
	(void)rhs;
	return *this;
}

const char *Factory::ValueOutOfRangeException::what() const noexcept {
	return _msg;
}