# `ergm.userterms`: User-specified Terms for the statnet Suite of Packages

[![Build Status](https://travis-ci.org/statnet/ergm.userterms.svg?branch=master)](https://travis-ci.org/statnet/ergm.userterms)
[![rstudio mirror downloads](https://cranlogs.r-pkg.org/badges/ergm.userterms?color=2ED968)](https://cranlogs.r-pkg.org/)
[![cran version](https://www.r-pkg.org/badges/version/ergm.userterms)](https://cran.r-project.org/package=ergm.userterms)
[![R build status](https://github.com/statnet/ergm.userterms/workflows/R-CMD-check/badge.svg)](https://github.com/statnet/ergm.userterms/actions)

A template package to demonstrate the use of user-specified statistics for use in 'ergm' models as part of the Statnet suite of packages.

## Public and Private repositories

To facilitate open development of the package while giving the core developers an opportunity to publish on their developments before opening them up for general use, this project comprises two repositories:
* A public repository `statnet/ergm.userterms`
* A private repository `statnet/ergm.userterms-private`

The intention is that all developments in `statnet/ergm.userterms-private` will eventually make their way into `statnet/ergm.userterms` and onto CRAN.

Developers and Contributing Users to the Statnet Project should read https://statnet.github.io/private/ for information about the relationship between the public and the private repository and the workflows involved.

## Latest Windows and MacOS binaries

A set of binaries is built after every commit to the repository. We strongly encourage testing against them before filing a bug report, as they may contain fixes that have not yet been sent to CRAN. They can be downloaded through the following links:

* [MacOS binary (a `.tgz` file in a `.zip` file)](https://nightly.link/statnet/ergm.userterms/workflows/R-CMD-check.yaml/master/macOS-rrelease-binaries.zip)
* [Windows binary (a `.zip` file in a `.zip` file)](https://nightly.link/statnet/ergm.userterms/workflows/R-CMD-check.yaml/master/Windows-rrelease-binaries.zip)

You will need to extract the MacOS `.tgz` or the Windows `.zip` file from the outer `.zip` file before installing. These binaries are usually built under the latest version of R and their operating system and may not work under other versions.
