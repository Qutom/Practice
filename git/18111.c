#include <stdio.h>

int calTime(int *heights, int targetHeight) {
	int result = 0;
	int temp;
	
	for (int i = 0; i < 257; i++) {
		temp = i - targetHeight;
		if ( temp < 0 ) {
			result += heights[i] * temp * (-1); //����� ���� * ��ȭ�ؾ��ϴ� �� ��  
		} else if ( temp > 0 ) {
			result += 2 * heights[i] * temp; // ����� ���� * 2�� * ��ȭ�ؾ��ϴ� �� �� 
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
	int heights[257]; //Index�� �ش��ϴ� ���̸� ������ ����� �ش� �迭�� ���Ҹ�ŭ ���� 
	 
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
	
	//�κ��丮 ������ �� + ���� �ʵ忡 �����ϴ� ���� ���� ���� ������ �ִ���̸� ���� 
	maxHeight = (totalHeight + block) / (n*m);
	if ( maxHeight > 256 ) {
		maxHeight = 256;
	}
	
	int bestHeight = minHeight;
	int bestTime = calTime(heights, minHeight);
	
	int time;
	
	//�ּ� ���� �Ʒ��δ� ���� �Ĵ� �͸� �þ�Ƿ� �ּ� ���� ~ �ִ� ���̸� ��� Ž�� 
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
