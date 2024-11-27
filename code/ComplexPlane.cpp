#include "ComplexPlane.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <complex>


using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size.x = pixelWidth;
	m_pixel_size.y = pixelHeight;

	m_aspectRatio = static_cast<float>(m_pixel_size.y) / m_pixel_size.x;
	
	m_plane_center.x = 0.0;
	m_plane_center.y = 0.0;
	m_plane_size = {BASE_WIDTH, BASE_HEIGHT* m_aspectRatio};
	m_zoomCount = 0;
	m_State = State::CALCULATING;
	m_vArray.setPrimitiveType(PrimitiveType::Points);
	m_vArray.resize(pixelWidth * pixelHeight);

}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
	if (m_State == State::CALCULATING)
	{
		for (int i = 0; i < m_pixel_size.y; i++) //y-axis loop
		{
			for (int j = 0; j < m_pixel_size.x; j++) //x-axis loop
			{
				m_vArray[j + i * m_pixel_size.x].position =  {static_cast<float>(j),static_cast<float>(i)};

				Vector2i coord(j, i);
				Vector2f complexCoord = ComplexPlane::mapPixelToCoords(coord);

				int iterations = ComplexPlane::countIterations(complexCoord);

				Uint8 r, g, b;

				ComplexPlane::iterationsToRGB(iterations, r, g, b);

				m_vArray[j + i * m_pixel_size.x].color = Color(r, g, b);
			}
		}
		m_State = State::DISPLAYING;
	}
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float sizeX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float sizeY = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size.x = sizeX;
	m_plane_size.y = sizeY;
	m_State = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float sizeX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float sizeY = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size.x = sizeX;
	m_plane_size.y = sizeY;
	m_State = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = ComplexPlane::mapPixelToCoords(mousePixel);
		m_State = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = ComplexPlane::mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text)
{
	stringstream output;
	
	output << "Mandelbrot Set" << endl;
	output << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")" << endl;
	output << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl;
	output << "Left-click to Zoom in" << endl;
	output << "Right-click to Zoom out" << endl;

	text.setString(output.str());
}

int ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c(coord.x, coord.y);
	complex<double> z = c;
	int i = 0;
	while (abs(z) < 2.0 && i < 64)
	{
		z = z * z + c;
		i++;
	}
	return i;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	long unsigned int range = MAX_ITER / 5;
		if (count == MAX_ITER)
		{
			r = 0;
			g = 0;
			b = 0;
		}
		else if (count < range)
		{
			r = 75;  
			g = 0;   
			b = 130; 
		}
		else if (count < 2 * range)
		{
			r = 0;
			g = 255;
			b = 255;
		}
		else if (count < 3 * range)
		{
			r = 0;
			g = 255;
			b = 0;
		}
		else if (count < 4 * range)
		{
			r = 255;
			g = 255;
			b = 0;
		}
		else
		{
			r = 255;
			g = 0;
			b = 0;
		}
	
}		

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	float real = ((static_cast<float>(mousePixel.x) / m_pixel_size.x) * m_plane_size.x) + (m_plane_center.x - m_plane_size.x / 2.0);
	float imaginary = ((static_cast<float>(mousePixel.y) / m_pixel_size.y) * m_plane_size.y) + (m_plane_center.y - m_plane_size.y / 2.0);

	return Vector2f(real, imaginary);

}
