#include "Header.h"

void Remove_Blanks_At_The_End( char *line ) {
	int i, k, newline_flag = 0;

	for ( k = 0; ; k++ ) {
		if ( line[k] == '\n' ) {
			newline_flag = 1;
			break;
		}
		else if ( line[k] == '\0' ) {
			break;
		}
	}
	//문자열 쭉 읽다가 줄넘김 문자 있으면 newline_flag를 1로 바꾸고 break
	//그렇게 쭉 읽다가 문자열 끝에 다다르면 break
	for ( i = k - 1; i >= 0; i-- ) {
		if ( line[i] != ' ' ) {
			break;
		}
	}
	//아까 읽은 문자열을 뒤에서부터 앞으로 읽어오면서 공백문자가 아니면 break
	//뭔가 이상함1 i=k-1부터이지 않을까..?
	if ( newline_flag == 1 ) {
		line[i + 1] = '\n';
		line[i + 2] = '\0';
	}
	//아까 읽은 문장이 줄넘김으로 끝났을 경우다
	//처음으로 공백이 아닌 부분을 줄넘김으로 바꾸고 그 다음을 EOS로 바꾼다
	//근데 i번째를 바꾸면 공백이 아닌 그 문자가 줄바꿈으로 바뀌니까 하나씩 뒤로 밀어준다
	else {
		line[i + 1] = '\0';
	}
	//그게 아니면 처음으로 공백문자 아닌 곳을 EOS로 바꾼다
	//이것도 뒤로 하나 밀어준다. 
}

void Get_Blanks_Chars( char *line, int Start, int *N_Blanks, int *N_Chars ) {
	int i, blank_flag = 0;
	*N_Blanks = *N_Chars = 0;

	for ( i = Start; ; i++ ) {
		if ( (line[i] == '\n') || (line[i] == '\0') ) {
			break;
		}
		//문자열을 읽다가 줄바꿈이나 EOS가 나오면 break
		else if ( line[i] == ' ' ) {//공백이 나왔을 때
			if ( blank_flag == 0 ) {//blank_flag가 0이면 *N_Blanks를 하나 증가
				++(*N_Blanks);
			}
			else {//blank_flag가 0이 아니면 break
				break;
			}
		}
		else {//공백도 아니고 줄바꿈도 아니고 EOS도 아니면
			//blank_flag를 1로 바꾸고 *N_Chars를 하나 증가
			blank_flag = 1;
			++(*N_Chars);
		}
	}
}

