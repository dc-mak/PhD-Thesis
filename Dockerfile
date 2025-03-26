# act -P=ubuntu-22.04=<this image> --pull=false --secret-file <file with "GITHUB_TOKEN=...">
# Should be fixed, https://github.com/catthehacker/docker_images/issues/125
# https://github.com/catthehacker/docker_images/issues/139
# Fixing path of this image (makes it surprisingly big)
FROM catthehacker/ubuntu:js-22.04
ENV PATH="/opt/acttoolcache/node/20.18.0/x64/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
