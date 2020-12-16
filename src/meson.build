project_sources += files('main.cpp')
project_sources += files([
	'Token.h',
	'Token.cpp',
	'Scanner.h',
	'Scanner.cpp'
])

ast_gen_exe = executable('astgen', 'astgen.cpp')
ast_gen_src = custom_target('gen-ast-classes',
						output: ['ast.h'],
						command: [ast_gen_exe])

project_sources += ast_gen_src[0]