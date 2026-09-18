#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH --job-name=FirstSlurm
#SBATCH --partition=instruction
#SBATCH --output=FirstSlurm.out
#SBATCH --error=FirstSlurm.err
#SBATCH -t 0-00:30:00
#SBATCH --cpus-per-task=2

hostname
