template <typename T>
Operand::Operand(std::string & value, eOperandType type) : _value(value), _type(type) {}

template <typename T>
Operand::Operand(Operand<T> const & rhs) {

	*this = rhs;
}

template <typename T>
Operand::~Operand() {}

template <typename T> std::string const &
Operand<T>::toString() const { return _value; }

template <typename T> eOperandType
Operand<T>::getType() const { return _type; }

template <typename T> int
Operand<T>::getPrecision() const { return _precision; }

template <typename T> Operand<T> const &
Operand<T>::operator=(Operand<T> const & rhs) {

	if (this == &rhs)
		return *this;

	_value = rhs.toString();
	_type = rhs.getType();
	return *this;
}

template <typename T> IOperand const *
Operand<T>::operator+(IOperand const & rhs) const {

	eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
	try
	{
		long double result = std::stold(toString()) + std::stold(rhs.toString());
	} 
	catch (std::exception &e) 
	{
		// HOW TO MANAGE ERRORS?
		std::cout << "Error : opearator+ : " << e.what() << std::endl;
		return nullptr;
	}
	return Factory().createOperand(type, std::to_string(result));
}

template <typename T> IOperand const *
Operand<T>::operator-(IOperand const & rhs) const {

	eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
	try
	{
		// порядок?
		long double result = std::stold(toString()) - std::stold(rhs.toString());
	} 
	catch (std::exception &e) 
	{
		// HOW TO MANAGE ERRORS?
		std::cout << "Error : opearator- : " << e.what() << std::endl;
		return nullptr;
	}
	return Factory().createOperand(type, std::to_string(result));
}

template <typename T> IOperand const *
Operand<T>::operator*(IOperand const & rhs) const {

	eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
	try
	{
		long double result = std::stold(toString()) + std::stold(rhs.toString());
	} 
	catch (std::exception &e) 
	{
		// HOW TO MANAGE ERRORS?
		std::cout << "Error : opearator* : " << e.what() << std::endl;
		return nullptr;
	}
	return Factory().createOperand(type, std::to_string(result));
}