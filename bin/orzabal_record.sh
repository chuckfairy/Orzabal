#!/bin/bash

#uses jack_capture

if [[ -z $1 ]]; then
    echo "USAGE: ./orzabal_record.sh <FILE_NAME.TYPE>";
    exit;
fi

jack_capture --channels 2 --port orzabal-client:input-* $1
