on:
  push:
    branches: [ "master" ]

env:
  PROJECT_ID: ${{ secrets.GKE_PROJECT }}
  GAR_LOCATION: us-central1 # TODO: update region of the Artifact Registry
  GKE_CLUSTER: cluster-1    # TODO: update to cluster name
  GKE_ZONE: us-central1-c   # TODO: update to cluster zone
  DEPLOYMENT_NAME: gke-test # TODO: update to deployment name
  REPOSITORY: samples # TODO: update to Artifact Registry docker repository
  IMAGE: static-site

jobs:
  setup-build-publish-deploy:
    name: Setup, Build, Publish, and Deploy
    runs-on: ubuntu-latest
    environment: production

    permissions:
      contents: 'read'
      id-token: 'write'

    steps:
    - name: Checkout
      uses: actions/checkout@v3

    # Configure Workload Identity Federation and generate an access token.
    - id: 'auth'
      name: 'Authenticate to Google Cloud'
      uses: 'google-github-actions/auth@v0'
      with:
        token_format: 'access_token'
        workload_identity_provider: 'projects/123456789/locations/global/workloadIdentityPools/my-pool/providers/my-provider'
        service_account: 'my-service-account@my-project.iam.gserviceaccount.com'


