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

	return (this->*_vecOfFunc[type])(value);
}

IOperand const *
Factory::createInt8(std::string const & value) const {

    auto val = std::stold(value);
    if (val < std::numeric_limits<int8_t>::min() || val > std::numeric_limits<int8_t>::max())
        throw OverflowErrorException("int8 value overflow");
	return new Operand<int8_t>(value, Int8);
}

IOperand const *
Factory::createInt16(std::string const & value) const {

	auto val = std::stold(value);
	if (val < std::numeric_limits<int16_t>::min() || val > std::numeric_limits<int16_t>::max())
		throw OverflowErrorException("int16 value overflow");
	return new Operand<int16_t>(value, Int16);
}

IOperand const *
Factory::createInt32(std::string const & value) const {

	auto val = std::stold(value);
	if (val < std::numeric_limits<int32_t>::min() || val > std::numeric_limits<int32_t>::max())
		throw OverflowErrorException("int32 value overflow");
	return new Operand<int32_t>(value, Int32);
}

IOperand const *
Factory::createFloat(std::string const & value) const {

	auto val = std::stold(value);
	if (val < -std::numeric_limits<float>::max() || val > std::numeric_limits<float>::max())
		throw OverflowErrorException("float value overflow");
	if (val < std::numeric_limits<float>::min())
		throw UnderflowErrorException("float value underflow");
	return new Operand<float>(value, Float);
}

IOperand const *
Factory::createDouble(std::string const & value) const {

	auto val = std::stold(value);
	if (val < -std::numeric_limits<double>::max() || val > std::numeric_limits<double>::max())
		throw OverflowErrorException("double value overflow");
	if (val < std::numeric_limits<double>::min())
		throw UnderflowErrorException("double value underflow");
	return new Operand<double>(value, Double);
}

/************************ EXCEPTIONS ****************************/

Factory::OverflowErrorException::OverflowErrorException(char const *msg) noexcept : std::runtime_error(msg), _msg(msg) {}

Factory::OverflowErrorException::OverflowErrorException(OverflowErrorException const &rhs) noexcept : std::runtime_error(rhs._msg) {

	*this = rhs;
}

Factory::OverflowErrorException::~OverflowErrorException() = default;

Factory::OverflowErrorException
&Factory::OverflowErrorException::operator=(Factory::OverflowErrorException const &rhs) noexcept {

	(void)rhs;
	return *this;
}

const char *Factory::OverflowErrorException::what() const noexcept {
	return _msg;
}


/************************ EXCEPTIONS ****************************/

Factory::UnderflowErrorException::UnderflowErrorException(char const *msg) noexcept : std::range_error(msg), _msg(msg) {}

Factory::UnderflowErrorException::UnderflowErrorException(UnderflowErrorException const &rhs) noexcept : std::range_error(rhs._msg) {

	*this = rhs;
}

Factory::UnderflowErrorException::~UnderflowErrorException() = default;

Factory::UnderflowErrorException
&Factory::UnderflowErrorException::operator=(Factory::UnderflowErrorException const &rhs) noexcept {

	(void)rhs;
	return *this;
}

const char *Factory::UnderflowErrorException::what() const noexcept {

	return _msg;
}