#include "header.h"

cameraInfo cameraInfomation;

void main()
{
	define_cameraInfo(cameraInfomation);
	mat H_rel_abs(5, 5);
	mat H_abs_phi(5, 5);
	mat H_phi_sphi(5, 5);
	mat H_T(5, 5);
	mat H_M(5, 5);
	mat H_sphi_phi(5, 5);

	define_H(H_rel_abs, H_abs_phi, H_phi_sphi, H_T, H_M, H_sphi_phi, cameraInfomation);

	mat sol(5, 1, fill::zeros);
	
	mat input(5, 1);
	//--------------------------------------------------------------------------
	int lens = cameraInfomation.K;//마이크로렌즈갯수
	int sensor = cameraInfomation.N;//마이크로레즈 한개당 센서 갯수
	mat imageCoord(4, 3);
	imageCoord <<0 << 0 << 2000 << endr
		<< 0 << 1000 << 2000 << endr
		<< 1000 << 1000 << 2000 << endr
		<< 1000 <<1000 << 2000 << endr;
	int world_x = 1000, world_y = 1000; //이미지 크기
	int input_width, input_height;
	colorimg** inputimg = ReadImage_color("C:\\Users\\김송란\\Documents\\GitHub\\Study\\lightfield\\cat.jpg", &input_width, &input_height);
	mat Pl1(1, 3), Pl2(1, 3); //s,t,u,v 저장할 변수
	mat unitvector(1, 3);
	mat Pp1(1, 3), Pp2(1, 3), Pp3(1, 3); //평면의 모서리 3개 좌표 변수
	mat nomalvector(1, 3); //법선벡터
	mat x(1, 3);//직선과 평면이 만나는 점
	colorimg** outimg = (colorimg**)IntAlloc2(lens*sensor, lens*sensor);
    colorimg** SubApertureImg = (colorimg**)IntAlloc2(lens*sensor, lens*sensor);
	mat a, b, c, d, sub_xy;
	int InOutFlag = 0;                           
	for (int k = 0; k < lens; k++)
	{
		for (int l = 0; l < lens; l++)
		{
			for (int i = 0; i < sensor; i++)
			{
				for (int j = 0; j < sensor; j++)
				{
					input << i << endr
						<< j << endr
						<< k << endr
						<< l << endr
						<< 1 << endr;
					sol = H_sphi_phi * H_M * H_T * H_phi_sphi * H_abs_phi * H_rel_abs *input;
					//cout << "행렬 원소 보기: " << endl << sol << endl;
					LineEquation(sol(0,0), sol(1,0), sol(2,0), sol(3,0), cameraInfomation.D, Pl1, Pl2, unitvector);//직선의 방정식
					PlaneEquation(imageCoord, Pp1, Pp2, Pp3, nomalvector); //이미지평면의 방정식
					CrossLinePlane(unitvector, nomalvector, Pp1, Pl1, x); //직선과 이미지평면이 만나는 점
					InterpolationCoor(x, a, b, c, d, sub_xy, input_width, input_height, world_x, world_y); //선형보간법 좌표 생성
					InOutFlag=detectInOut(imageCoord, x);
					rawimage(InOutFlag,sensor*k+i,sensor*l+j,input_width,input_height, inputimg, outimg, a, b, c, d, sub_xy);		//이미지생성
				}
			}

		}

	}
	
	for (int i = 0; i < sensor; i++)
	{
		for (int j = 0; j < sensor; j++)
		{
			MakeSubApertureImages(i, j, lens, sensor, outimg, SubApertureImg);
		}

	}
	

	WriteImage_color("C:\\Users\\김송란\\Documents\\GitHub\\Study\\lightfield\\영상출력테스트5.bmp", outimg, lens*sensor, lens*sensor);
	WriteImage_color("C:\\Users\\김송란\\Documents\\GitHub\\Study\\lightfield\\영상출력테스트sub5.bmp", SubApertureImg, lens*sensor, lens*sensor);

	
	
	

}