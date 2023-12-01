C_FILES = Raytracer.cpp -lglfw3 -lglew32 -lopengl32 -lgdi32

APP_LINKERS :=  -lglfw3 -lglew32 -lopengl32 -lgdi32

build: 
	g++ $(C_FILES)