<template>
  <div class="circle-box">
    <img :src="src" :alt="alt" class="circular-image" />
  </div>
</template>

<script setup>
defineProps({
  src: {
    type: String,
    required: true,
  },
  alt: {
    type: String,
    default: '',
  },
  borderWidth: {
    type: String,
    default: '5px'
  },
  borderColor: {
    type: String,
    default: 'white'
  }
});
</script>

<style scoped>
.circle-box {
  display: inline-block;
  border: v-bind(borderWidth) solid v-bind(borderColor); /* Adjust color and thickness as needed */
  border-radius: 50%;
  overflow: hidden;
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2); /* Optional: Adds a shadow effect */
}

.circular-image {
  display: block;
  max-width: 100%;
  height: auto;
}
</style>