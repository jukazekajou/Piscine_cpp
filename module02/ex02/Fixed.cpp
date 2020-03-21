#include "Fixed.hpp"

Fixed::Fixed()
{
	_n = 0;
}

Fixed::~Fixed()
{
}

Fixed::Fixed(const Fixed& ori)
{
	_n = ori.getRawBits();
}

void Fixed::operator = (const Fixed& ori)
{
	this->_n = ori.getRawBits();
}

int Fixed::getRawBits(void) const
{
	return (_n);
}

void Fixed::setRawBits(int const raw)
{
	_n = raw;
}

// Other constructors
Fixed::Fixed(const int n)
{	
	setRawBits(n << 8);
}

Fixed::Fixed(const float f)
{
	// i write the dec part into a stream to get the exast length, to_string gives bad results;
	unsigned char raw[sizeof(int)];
	int integ = (int)f;
	int dec_i;
	std::stringstream ost;
	float dec;
	
	int raw2 = 0;
	raw[0] = 0;
	
	ost << f;
	std::string fs = ost.str();
	fs = "0" + fs.substr(fs.find('.'));
	dec = std::stof(fs);
	
	for (int i = 0; i < 8; i++)
	{
		dec = dec * 2;
		if (dec >= 1)
		{
			raw[0] += pow(2, i);
			dec = dec - 1;
		}
	}

/*	std::string b = ost.str();
	std::cout << b << std::endl;
	if (dec > 0)
		b = b.substr(2);
	else if (dec != 0)
		b = b.substr(3);
	if (dec != 0)
		dec_i = std::stoi(b);
	else 
		dec_i = 0;
	
	std::cout << "la " << dec_i << std::endl;
	raw[0] = (unsigned char)dec_i; // not sure
	*/

	memcpy(&raw[1], &integ, 3);

	memcpy(&raw2, raw, sizeof(int));
	setRawBits(raw2);
}

int Fixed::getFixedPoint()
{
	return (_fixed_point);
}

int Fixed::toInt(void) const
{
	return (_n >> 8);
}

float Fixed::toFloat(void) const
{
	float f;
	float dec;
	int n = _n;
	unsigned char rawc[sizeof(float)];
	std::string b;

	memcpy(rawc, &n, sizeof(float));
	
	b = std::to_string((int)(rawc[0]));
	int size = -b.size();
	dec = ((int)rawc[0] * std::pow(10, size));
	
	f += (_n >> 8);
	if (f >= 0)
		f += dec;
	else
		f -= dec;	
	return (f);
}

std::ostream& operator << (std::ostream &out, Fixed& b)
{
	unsigned char raw[sizeof(int)];
	int raw_i = b.getRawBits();

	memcpy(raw, &raw_i, sizeof(int));
	
	std::string s = "";
	s.append(std::to_string(raw_i >> 8));
	s.push_back('.');
	s.append(std::to_string((int)raw[0]));
	return (out << s);
}

/* Comp Overloads */

bool operator == (const Fixed& a, const Fixed& b)
{
	if (a.getRawBits() == b.getRawBits())
		return (1);
	return (0);
}

bool operator != (const Fixed& a, const Fixed& b)
{
	if (a.getRawBits() != b.getRawBits())
		return (1);
	return (0);
}

bool operator < (const Fixed& a, const Fixed& b)
{
	if (a.getRawBits() < b.getRawBits())
		return (1);
	return (0);
}
bool operator <= (const Fixed& a, const Fixed& b)
{
	if (a.getRawBits() <= b.getRawBits())
		return (1);
	return (0);
}

bool operator > (const Fixed& a, const Fixed& b)
{
	if (a.getRawBits() > b.getRawBits())
		return (1);
	return (0);
}

bool operator >= (const Fixed& a, const Fixed& b)
{
	if (a.getRawBits() >= b.getRawBits())
		return (1);
	return (0);
}

/* Operations overload */

Fixed operator + (const Fixed& a, const Fixed& b)
{
	
	std::cout << "a " << a.toFloat() << " b " << b.toFloat() << std::endl;
	std::cout << a.toFloat() + b.toFloat() << std::endl;
	float res = float(a.toFloat() + b.toFloat());
	std::cout << res << std::endl;
	Fixed c(res);
	return (c);
}

float operator - (const Fixed& a, const Fixed& b)
{
	return (a.toFloat() - b.toFloat());
}

Fixed operator * (const Fixed& a, const Fixed& b)
{
	Fixed c;

	c.setRawBits(a.getRawBits() << b.getRawBits());
	return (c);
}

float operator / (const Fixed& a, const Fixed& b)
{
	return (a.toFloat() / b.toFloat());
}