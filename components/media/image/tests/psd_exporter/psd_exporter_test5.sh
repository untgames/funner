#/bin/sh
echo Results of psd_exporter_test5:
psd-exporter data/test.psd --silent -o my.xlayermap --no-layers
cat my.xlayermap
rm -f my.xlayermap
