#!/bin/bash

shopt -s globstar nullglob extglob



for f in **/*.@(hpp|h); do
  cat "/home/serge/Desktop/ram001/LICENSE.HEAD" $f > $f.new
  mv $f.new $f
done
