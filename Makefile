project_name = windshield

compile:
	@cmake --build build

launch:
	@./build/windshield

all:
	@make compile && make launch
