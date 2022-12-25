
function calc {

awk "BEGIN { printf \"%.3f GB\n\", $*}";

}
