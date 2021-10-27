#pragma once

namespace Algorithms
{
	std::vector<Vector2> DrawCircle(int xc, int yc, int x, int y)
	{
		std::vector<Vector2> vertices;
		vertices.push_back(Vector2(xc+x, yc+y));
		vertices.push_back(Vector2(xc-x, yc+y));
	    vertices.push_back(Vector2(xc+x, yc-y));
	    vertices.push_back(Vector2(xc-x, yc-y));
	    vertices.push_back(Vector2(xc+y, yc+x));
	    vertices.push_back(Vector2(xc-y, yc+x));
	    vertices.push_back(Vector2(xc+y, yc-x));
	    vertices.push_back(Vector2(xc-y, yc-x));
	    return vertices;
	}
	 
	std::vector<Vector2> CircleBres(int xc, int yc, int r)
	{
	    int x = 0, y = r;
	    int d = 3 - 2 * r;
	    std::vector<Vector2> points;
	    points.insert(points.end(), DrawCircle(xc, yc, x, y).begin(), DrawCircle(xc, yc, x, y).end());
	    while (y >= x)
	    {
	        // for each pixel we will
	        // draw all eight pixels
	         
	        x++;
	 
	        // check for decision parameter
	        // and correspondingly
	        // update d, x, y
	        if (d > 0)
	        {
	            y--;
	            d = d + 4 * (x - y) + 10;
	        }
	        else
	        {
	            d = d + 4 * x + 6;
	        }
	        points.insert(points.end(), DrawCircle(xc, yc, x, y).begin(), DrawCircle(xc, yc, x, y).end());
	    }
	    for(Vector2 vec:points)
	    {
	    	std::cout<<vec.ToString()<<std::endl;
	    }
	    return points;
	}
}