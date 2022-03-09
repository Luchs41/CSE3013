#include "header.h"

int main()
{
	int input;
	int i;
	int page;
	//변수 선언
	//input은 받을 case 개수, page는 그 case에서 계산할 page수

	scanf("%d", &input);	//input 설정

	for(i = 0; i < input; i++)
	{
		scanf("%d", &page);
		countNum(page);
	}
	//input만큼 page들을 입력받은 후, countNum 함수로 각 페이지를 구성하는 각 숫자의 개수를 계산하고 출력함
	return 0;
}
