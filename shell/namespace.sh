#!/bin/bash
var=100
function ch_var() {
  local var=200;
}
echo "Before function var:$var"
ch_var
echo "After function var:$var"