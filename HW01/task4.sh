#!/usr/bin/env bash
#SBATCH --job-name=FirstSlurm
#SBATCH --partition=instruction
#SBATCH --output=FirstSlurm.out
#SBATCH --error=FirstSlurm.err
#SBATCH --cpus-per-task=2

hostname