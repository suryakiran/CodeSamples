import os, sys, re
import glob

def getFilesByExtn(ctx, extn):
    files = glob.glob(ctx.path.abspath() + '/*.%s' % extn)
    return [os.path.relpath(p, ctx.path.abspath()) for p in files]

def getCxxFiles(ctx):
    return getFilesByExtn(ctx, 'cxx')

def getHxxFiles(ctx):
    return getFilesByExtn(ctx, 'hxx')
