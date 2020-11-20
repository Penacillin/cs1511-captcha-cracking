#ifndef DATA_H
#define DATA_H


#define N_OF_METRICS 38

typedef enum Metric Metric;
enum Metric
{
	mhorBalance,
	mverBalance,
	mtallness,
	mhole_size_fraction,
	mholes,
	mdensity,
	mmaxVertical,
	mmaxHorizontal,
	maverageWidth,
	mmidLeftDensity,
	mbotRightDensity,
	mvertPosOfHole,
	msdHorBalance,
	mmeanWidthOfThree,
	mhorBalTop,
	msteepestFallTopLeft,
	msteepestFallBotRight,
	msteepestFallMidLeft,
	mbotHorBalance,
	mdeepestLeftBotRight,
	mvertsBot,
	mmaxDiffVertBot,
	mSDgradBotLeft,
	mSDgradBotRight,
	mdeltaTR,
	msteepestFallBotLeft,
	msteepestFallTopRight,
	msmoothnessMidLeft,
	mfractionThree,
	maverageGradMidRight,
	mshallowestBotLeft,
	mdeltaBL,
	msmoothnessMidRight,
	mmaxGradChangeBR,
	mmaxGradChangeBL,
	mmaxHorBot,
	mmaxWidthDiffBot,
	mtopThirdRight
	//leftchecks
};

double getSum(double digit_metrics[100][N_OF_METRICS], Metric metric);
double getAverage(double digit_metrics[100][N_OF_METRICS], Metric metric);
double get_stddevS(double digit_metrics[100][N_OF_METRICS], Metric metric);

void read_stats_table(double digit_stats[10][N_OF_METRICS][2]);

int getStatsFor(int dig, double digit_stat[100][N_OF_METRICS]);
void create_summary_csv();

#endif
