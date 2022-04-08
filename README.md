# Harbor-Crate

Simple process containerization (like Docker) using Linux system calls.

## Terminology:
> What is a crate?

A crate is an instance of a process container. The crate acts as the parent process for all subprocesses. i.e.

demo_crate (PID: 31423)<br>\\<br>&nbsp;&nbsp;/bin/bash (PID: 3)<br>
&nbsp;&nbsp;/bin/top (PID: 4)

Crates can be isolated in a number of ways from the host machine. This is achieved using `cgroups`. The following process attributes can _currently_ be isolated:
- File system (root)
- Network
- Processes

## Usage
`harbor-crate mode [arguments ...]`
### mode

---
#### create: create a new process container (crate)

##### Arguments:
`[name=x] [flavor=x] [network=x] [mount=x:y] [hostname=x] [-v]`
- `name`: the name of this container. If not specified, will be the container's ID
- `flavor`: the filesystem to use within the crate. By default this uses [alpine-mini-root](https://alpinelinux.org/downloads/). This argument is not yet implemented
- `network`: the network mode to use in the crate
    - isolated: crate is isolated from the host machine's network
    - bridged: crate communicates using the same network connection as the host machine
- `mount`: can be specified multiple times. mounts the given absolute path on the host machine to the absolute path in the crate
    - x: host machine absolute path to directory or file
    - y: crate absolute path where the directory or file will be mounted
- `hostname`: change the hostname of the container. By default, this is the container ID
- `-v`: enable verbose output

##### Example Usage:
```bash
$ harbor-crate create -name=demo_crate -mount /home/username/welcome.txt:/home/crate/welcome.txt -hostname=demo
harbor: successfully built demo_crate (9be17fc2)
```

---
#### delete: delete a running process crate

##### Arguments:
`crate_id [-v]`
- `crate_id`: the id of the container to delete
- `-v`: enable verbose output

##### Example Usage:
```bash
$ harbor-crate delete 9be17fc2
harbor: stopping 9be17fc
harbor: crate deleted
```

---
#### execute: attach a process to a running crate
##### Arguments:
`crate_id executable_path [-detach]`
- `crate_id`: the id of the crate
- `[-detach]`: the process will run as a detached process (separate from your tty)

##### Example Usage:
```bash
$ harbor-crate execute 9be17fc2 /bin/bash
harbor: attached process /bin/bash to 9be17fc2 (pid: 72)

root@demo $
```

---
#### list: show all running crates

##### Example Usage:
```bash
$ harbor-crate list
CRATE_ID    CRATE_NAME      HOST_PID    NETWORK_MODE    STATUS
9be17fc2    demo_crate      31423       isolated        running
```
----
