#include <stdio.h>

int calTime(int *heights, int targetHeight) {
	int result = 0;
	int temp;
	
	for (int i = 0; i < 257; i++) {
		temp = i - targetHeight;
		if ( temp < 0 ) {
			result += heights[i] * temp * (-1); //기둥의 갯수 * 변화해야하는 블럭 수  
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
