#pragma once
class Timer //计时器类(将帧转化为以秒为单位)
{
private:
	int fps; //每秒调用帧函数的次数 60
	int times;//
	int time;//记录每调用6次帧函数的时间 100ms
public:
	Timer();
	void run() { //执行
		times++;
		if (times>6)
		{
			time++;
			times = 0;
		}
	}
	int getTime(); //返回时间 100ms 为单位
	~Timer();
};

