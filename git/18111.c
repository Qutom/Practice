/*
	백준 18111번 - 마인크래프트 
	https://www.acmicpc.net/problem/18111
*/

/*
	1. 높이 0~256에 해당하는 기둥의 수를 저장하는 배열을 만든다.
	2. 값을 받아와 저장한다.
	3. 구현 가능한 최대 높이는 (인벤토리의 블럭 수 + 캘 수 있는 블럭의 수) / ( 집터의 넓이) 이므로 이를 구한다.
	4. 최소 높이가 1 이상인 경우, 1 미만의 값을 목표 높이로 설정하면, 캐야하는 블럭의 수가 집터의 넓이 만큼 증가한다.
	5. 3, 4에 따라, for문을 통해 최소 높이 ~ 최대 높이 사이의 모든 높이를 목표로 각각 선택했을때의 소요 시간을 구한다. 
	6. 소요 시간은 어떤 높이 h에 목표 높이를 뺀 값을 x라고 할때, x가 음수이면, 실제 높이가 목표 높이 보다 낮음을 의미하므로
	   (기둥의 갯수) * x * (-1) 만큼의 시간이 소요되며,  x가 0이상이면 실제 높이가 목표보다 높음을 의미하므로,
	   (기둥의 갯수) * x 개의 블럭을 캐야한다. 따라서 (기둥의 갯수) * x * 2 만큼의 시간이 소요된다.
	7. 모든 높이인 0 ~ 256에 6번과 같은 방법을 적용하여 시간을 구한다.
	8. 가장 낮은 소요 시간을 가지는 가장 큰 높이를 구한다. 

*/
#include <stdio.h>

int calTime(int *heights, int targetHeight) {
	int result = 0;
	int temp;
	
	for (int i = 0; i < 257; i++) {
		temp = i - targetHeight;
		if ( temp < 0 ) {
			result += heights[i] * temp * (-1); //기둥의 갯수 * 설치해야하는 블럭 수  
		} else if ( temp > 0 ) {
			result += 2 * heights[i] * temp; // 기둥의 갯수 * 2초 * 변화해야하는 블럭 수 
		}
	}
	return result;
} 

int main(void) {
	int block;
	int n;
	int m;
	int totalHeight = 0;
	int maxHeight;
	int minHeight = 256;
	scanf("%d %d %d", &n, &m, &block);
	int heights[257]; //Index에 해당하는 높이를 가지는 기둥이 해당 배열의 원소만큼 존재 
	 
	for (int i = 0; i < 257; i++) {
		heights[i] = 0;
	}
	
	int val;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &val);
			totalHeight += val;
			heights[val]++;
		
			if ( minHeight > val ) {
				minHeight = val;
			} 
		}
	}
	
	//인벤토리 내부의 블럭 + 현재 필드에 존재하는 블럭을 합쳐 구현 가능한 최대높이를 구함 
	maxHeight = (totalHeight + block) / (n*m);
	if ( maxHeight > 256 ) {
		maxHeight = 256;
	}
	
	int bestHeight = minHeight;
	int bestTime = calTime(heights, minHeight);
	
	int time;
	
	//최소 높이 아래로는 땅을 파는 것만 늘어나므로 최소 높이 ~ 최대 높이를 모두 탐색 
	for (int i = minHeight+1; i < maxHeight+1; i++) {
		time = calTime(heights, i);
		if ( bestTime >= time ) {
			bestTime = time;
			if ( bestHeight < i ) {
				bestHeight = i;
			}
		}	
	}
	
	
	printf("%d %d", bestTime, bestHeight);
	
}
