#pragma warning(disable: 4996)

#define ENABLE_PROFILER 1

#if (ENABLE_PROFILER == 1)
	#define PROFILER_SETUP \
	static clock_t ___chr = 0; \
	clock_t ___time; \
	float ___time_sec; \
	char *___dsc;

	#define PROFILER_INIT \
	___chr = clock() ;

	#define PROFILER_TRIG(s) \
	___time = clock() - ___chr; \
	___time_sec = ((float)___time / 1000); \
	___dsc = s; \
	printf("%s:%f\n", ___dsc, ___time_sec);
#else
	#define PROFILER_SETUP
	#define PROFILER_INIT
	#define PROFILER_TRIG(s)
#endif
