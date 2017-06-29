sudo /etc/init.d/ntp stop
until ping -nq -c3 2.si.pool.ntp.org; do
   echo "Waiting for network..."
done
sudo ntpdate -s time.nist.gov
sudo /etc/init.d/ntp start
