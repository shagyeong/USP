if($#ARGV < 0) {
    &usage;
}

foreach $file (@ARGV) {
    unless( open(FILE, $file) ) {
        printf(STDERR "\n%s은 열 수 없습니다.\n", $file);
        next;
    }

    printf("%s:\n", $file);
    &hexdump;
    close(FILE);
}

sub hexdump {
    local($address, $count, $buf, @binary, $i, $string);
    for($address =0; ($count=read(FILE, $buf, 16)); $address += $count) {
        #...
    }
}

#...