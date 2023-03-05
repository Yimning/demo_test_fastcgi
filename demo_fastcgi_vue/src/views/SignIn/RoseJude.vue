<template>
    <div id="app">
        <router-view />
    </div>
</template>
 
<script>
export default {
    name: 'App',    
    created() {
        if (this.$store.getters.getUser.roseID == '1') {
            if (this.$store.getters.getUser.roseName == '教师管理员') {
                this.$router.push('/attendenceRecords');
            } else {
                this.$router.push('/teachAttendenceRecords');
            }
        }
    },
    methods: {
    }
}; 
</script>

