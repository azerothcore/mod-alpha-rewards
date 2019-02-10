#!/usr/bin/env bash

MOD_ALPHAREWARDS_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_ALPHAREWARDS_ROOT"/conf/conf.sh.dist"

if [ -f $MOD_ALPHAREWARDS_ROOT"/conf/conf.sh" ]; then
    source $MOD_ALPHAREWARDS_ROOT"/conf/conf.sh"
fi