#include "headfile.h"
//Border Detect
void borderDetect(uint8 in[][160],uint8 out[][160]){
		uint8 i,left,right,color=in[120][80];
		for(i=128;i>120;i--){
			for(left=80;(in[i][left]==in[i][left-1])&&(left>1);left--){
			}
			for(right=80;(in[i][right]==in[i][right+1])&&(right<158);right++){
			}
			out[i][left]=103;
			out[i][left+1]=103;
			out[i][left/2+right/2]=100;
			out[i][right]=106;
			out[i][right-1]=106;
		}
		for(;i>1;i--){
			if(in[i-1][left]!=color){
				for(;in[i][left]==in[i][left+1];left++){
				}
			}
			else{
				for(;(in[i][left]==in[i][left-1])&&(left>1);left--){
				}
			}
			if(in[i-1][right]!=color){
				for(;in[i][right]==in[i][right-1];right--){
				}
			}
			else{
				for(;(in[i][right]==in[i][left+1])&&(right<158);right++){
				}
			}
			out[i][left]=103;
			out[i][left+1]=103;
			out[i][left/2+right/2]=100;
			out[i][right]=106;
			out[i][right-1]=106;
		}
}