#!/bin/bash

## App Name
AppName='-o server'

## Compiler
CC='gcc'

## Libs
Libs='-pthread'

## Source files
SRCFiles=`find -regex '.*/.*\.\(c\|cpp\|h\)$' -print0 | xargs -0`

## Compile
eval "$CC $AppName $Libs $SRCFiles"
