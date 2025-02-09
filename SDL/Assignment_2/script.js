function formValidation() {
	const userid = document.registration.userid;
	const passid = document.registration.passid;
	const username = document.registration.username;
	const email = document.registration.email;
	const country = document.registration.country;
	const gender = document.registration.gender;

	if (!validateLength(userid, 5, 12, "User ID")) return false;
	if (!validateLength(passid, 7, 12, "Password")) return false;
	if (!validateName(username)) return false;
	if (!validateEmail(email)) return false;
	if (!validateDropdown(country, "Country")) return false;
	if (!validateGender(gender)) return false;

	alert("Registration Successful!");
	return true;
}

function validateLength(field, min, max, fieldName) {
	if (field.value.length < min || field.value.length > max) {
		alert(`${fieldName} must be between ${min} and ${max} characters.`);
		field.focus();
		return false;
	}
	return true;
}

function validateName(nameField) {
	if (!/^[A-Za-z\s]+$/.test(nameField.value)) {
		alert("Name can only contain letters and spaces.");
		nameField.focus();
		return false;
	}
	return true;
}

function validateEmail(emailField) {
	const emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
	if (!emailPattern.test(emailField.value)) {
		alert("Please enter a valid email address.");
		emailField.focus();
		return false;
	}
	return true;
}

function validateDropdown(dropdown, fieldName) {
	if (dropdown.value === "Default") {
		alert(`Please select a ${fieldName}.`);
		dropdown.focus();
		return false;
	}
	return true;
}

function validateGender(genderField) {
	const genders = document.getElementsByName("gender");
	if (![...genders].some(gender => gender.checked)) {
		alert("Please select a gender.");
		return false;
	}
	return true;
}
