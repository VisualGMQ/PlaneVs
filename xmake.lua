target("PlaneFight")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("include")
    set_languages("c++17")
     on_load(function (target)
        target:add(find_packages("SDL2", "SDL2_image", "GLEW", "glm"))
    end)
    add_frameworks("OpenGL")
