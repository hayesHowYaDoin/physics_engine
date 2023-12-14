# Prompt the user for their first and last name
echo "Enter your first and last name: "
read name

# Prompt the user for their email address
echo "Enter the email address associated with your github account: "
read email

# Prompt the user for their github username
echo "Enter your github username: "
read username

# Prompt the user for their github personal access token
echo "Enter your github personal access token (this will not be printed to the console): "
read -s token

# Set the git configuration settings for the user's local git repository
git config user.name "$name"
git config user.email "$email"
git config --global url."https://$username:$token@github.com/".insteadOf "https://github.com/"
