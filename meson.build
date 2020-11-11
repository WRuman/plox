project('plox', 'cpp', 
	version: '1.0',
	meson_version: '>= 0.50.0',
	default_options: ['cpp_std=c++17', 'werror=true', 'warning_level=3']
)

# All build files throughout the project should append to this list
project_sources = []


subdir('src') # Defines variable 'main_source'
executable('plox', main_source)
