top = '.'
out = 'build'
from waflib.Configure import conf

tools = {
    'builtin':
    ['compiler_cxx', 'boost', 'python'],

    'custom':
    [],
}

def options(ctx):
    ctx.add_option('--prefix', action='store', default=out, help='prefix dir')
    [ctx.load(t) for t in tools['builtin']]
    [ctx.load(t, tooldir='tools') for t in tools['custom']]

def configure(ctx):                                                                             
    print ('Configuring the project in ' + ctx.options.prefix)
    [ctx.load(t) for t in tools['builtin']]
    [ctx.load(t, tooldir='tools') for t in tools['custom']]
    ctx.check_boost(lib = ['system', 'filesystem', 'thread', 'serialization'])
    ctx.recurse('Boost')

def build(bld):
    bld.env.append_value('INCLUDES', [bld.path.abspath()])
    bld.recurse('CommandLineArgs')
    bld.recurse('Boost')

def install(ctx):
    print type(ctx)
