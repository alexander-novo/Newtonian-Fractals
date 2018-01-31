#include "main.h"

int main(int argc, char** argv) {
	run();

	return 0;
}

void run() {
	double radius = 5;
	double delta = radius / 1000.0;
	comp num;
	comp _num;
	comp prev_num;
	comp z;
	vec3 rgb;
	int vertexDimensions = radius / delta * 2;

	time_t now = time(NULL);
	time_t _now;

	long long numNewtonMethod = 0;
	long long numPerCent = vertexDimensions * vertexDimensions / 100;
	int perCents = 0;
	long long counter = 0;
	unsigned remaining;
	float speed;

	typedef unsigned char uchar;
	std::ofstream fout("fractal.tga", std::ios::binary | std::ios::out | std::ios::trunc);

	// this is the tga header it must be in the beginning of
	// every (uncompressed) .tga
	char TGAheader[12] = {0,0,2,0,0,0,0,0,0,0,0,0};
	// the header that is used to get the dimensions of the .tga
	// header[1]*256+header[0] - width
	// header[3]*256+header[2] - height
	// header[4] - bits per pixel
	// header[5] - ?
	char header[6]={(vertexDimensions%256),
	                (vertexDimensions/256),
	                (vertexDimensions%256),
	                (vertexDimensions/256),24,0};
	
	fout.write(TGAheader, 12);
	fout.write(header, 6);
	
//	// write out the TGA header
//	fwrite(TGAheader, sizeof(uchar), 12, shot);
//	// write out the header
//	fwrite(header, sizeof(uchar), 6, shot);
	
	
	std::cout << "Calculated: 0%\r" << std::flush;
	//generate our vertices
	for(int y = 0; y < vertexDimensions; y++) {
		for(int x = 0; x < vertexDimensions; x++) {
			num = comp(-radius + x * delta, radius - y * delta);
			_num = num;
//			num = 0;
//			_num = comp(-radius + x * delta, radius - y * delta);
			int i;
			for(i = 0; i < 20; i++) {
				prev_num = num;
				num -= easy(num) / easyPrime(num);
				//num -= (easy(num) + _num) / easyPrime(num);
				if(prev_num == num) {
					break;
				}
			}
			numNewtonMethod += i;

			rgb = zToRGB(num);
			fout.put(rgb.r);
			fout.put(rgb.g);
			fout.put(rgb.b);

			counter++;
			if(counter == numPerCent) {
				perCents++;
				_now = time(nullptr);
				remaining = 100 - perCents;
				speed = float(_now - now) / perCents;
				std::cout << "                                                                     \r"
					<< "Calculated: " << perCents << "% - Time Taken: " << _now - now << "s - Est. Time Remaining: " << unsigned(speed * remaining) << "s\r" << std::flush;
				counter = 0;
			}
		}
	}

	std::cout << '\n'
		<< "Time taken to generate vertices: " << time(NULL) - now << " s" << std::endl
		<< "Avg. number of Newton's Method iterations: " << numNewtonMethod / ((double)vertexDimensions * vertexDimensions) << std::endl;
	now = time(NULL);

	fout.close();
}

comp easy(const comp& num) {
	//return pow(num, 3) + 1.0l;
	return pow(num, 5) + 1.0l;
	//return sinh(num);
	//return (long double) log(abs(num));
	//return pow(num, 3) + exp(num);
	//return sin(exp(num) * num);
	//return pow(num,5) + 4.0l * pow(num,4) + 3.0l * pow(num,2) - 12.0l;
	//return num * exp(-3.0l * pow(num, 5)) * sin(pow(num, 2));
	//return (long double) log(abs(sin(num))) + num;
	//return sin(num) / cos(num);
	//return sin(tan(num));
	//return tan(num * exp(num));
	//return sinh(exp(num));
}

comp easyPrime(const comp& num) {
	//return 3.0l * pow(num, 2);
	return 5.0l * pow(num, 4);
	//return cosh(num);
	//return 1.0l / num;
	//return 3.0l * pow(num, 2) + exp(num);
	//return exp(num) * cos(exp(num) * num) * (1.0l + num);
	//return 5.0l * pow(num,4) + 16.0l * pow(num,3) + 6.0l * num;
	//return -1.0l * exp(-3.0l * pow(num, 5)) * ((15.0l * pow(num, 5) - 1.0l) * sin(pow(num, 2)) - 2.0l * pow(num, 2) * cos(pow(num, 2)));
	//return cos(num) / sin(num);
	//return pow(1.0l / cos(num), 2);
	//return cos(tan(num)) * pow(1.0l / cos(num), 2);
	//return 1.0l / pow(cos(num * exp(num)), 2) * (exp(num) + num * exp(num));
//	comp expNum = exp(num);
//	return expNum * cosh(expNum);
}

vec3 zToRGB(comp z) {
	vec3 rgb;
	long double theta = std::arg(z);
	long double r = std::abs(z);
	long double h = theta * 3 / M_PI;

	rgb.r = CLAMP(2.0 - std::abs(h), 0, 1) * 255.0l;
	rgb.g = CLAMP(std::abs(h - 1.0) - 1.0, 0, 1) * 255.0l;
	rgb.b = CLAMP(std::abs(h + 1.0) - 1.0, 0, 1) * 255.0l;

	return rgb;
}

std::ostream& operator<<(std::ostream& stream, const vec3 & vector) {
	stream << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
	return stream;
}